#include "filter.h"

#define sig 1
#define hi 100
#define lo 35

void rstzr::gray(std::vector<component_t> &matrix, std::vector<component_t> &pic,
                 size_t width, size_t height)
{
    std::cout << "gray\n";
    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int z = 0; z < 3; z++)
            {
                auto red = matrix[width * y + x];
                auto green = matrix[height * width + width * y + x];
                auto blue = matrix[height * width * 2 + width * y + x];

                pic[width * y + x] = (int)((0.299 * red) + (0.587 * green) + (0.144 * blue));
            }
        }
    }
    std::cout << "Length of array = " << static_cast<unsigned>((component_t)(sizeof(matrix) / sizeof(matrix[0]))) << std::endl;
    std::cout << "Length of array = " << (sizeof(pic) / sizeof(pic[0])) << std::endl;
}

/**
 * Code from: https://github.com/sorazy/canny 
 */
std::vector<int> rstzr::canny(std::vector<component_t> matrix, size_t width, size_t height)
{
    std::cout << "w " << width << "h " << height << "\n";
    size_t size = width * height;
    std::cout << "Length of array = " << matrix.size() << std::endl;

    std::vector<component_t> pic(size);
    gray(matrix, pic, width, height);

    std::vector<component_t> mag(size);
    auto x = new double[size];
    auto y = new double[size];
    auto final = new component_t[size];

    // Create the magnitute matrix
    magnitude_matrix(pic, mag, x, y, width, height);
    std::cout << "map-1\n";
    // Get all the peaks and store them in vector
    std::map<int, int> peaks;
    std::cout << "map\n";
    std::vector<Point2D *> v = peak_detection(mag, peaks, x, y, width, height);

    // Go through the vector and call the recursive function and each point. If the value
    // in the mag matrix is hi, then immediately accept it in final. If lo, then immediately
    // reject. If between lo and hi, then check if it's next to a hi pixel using recursion
    std::map<int, int> h;
    component_t a, b;
    std::vector<int> result;
    std::cout << "v " << v.size();
    for (auto i = 0u; i < v.size(); i++)
    {
        a = v.at(i)->x();
        b = v.at(i)->y();

        if (mag[a + b * width] >= hi)
        {
            result.push_back(a + b * width);
            final[a + b * width] = 255;
        }
        else if (mag[a + b * width] < lo)
            final[a + b * width] = 0;
        else
            recursiveDT(mag, final, h, peaks, a, b, 0, height, width, result);
    }

    delete x;
    delete y;

    return result;
}

void rstzr::magnitude_matrix(std::vector<component_t> pic, std::vector<component_t> mag,
                             double *x, double *y,
                             component_t width, component_t height)
{
    const int dim = 6 * sig + 1, cent = dim / 2;
    auto maskx = new double[dim][dim];
    auto masky = new double[dim][dim];

    // Use the Gausian 1st derivative formula to fill in the mask values
    for (int p = -cent; p <= cent; p++)
    {
        for (int q = -cent; q <= cent; q++)
        {
            maskx[p + cent][q + cent] = q * exp(-1 * ((p * p + q * q) / (2 * sig * sig)));
            masky[p + cent][q + cent] = p * exp(-1 * ((p * p + q * q) / (2 * sig * sig)));
        }
    }

    // Scanning convolution
    double sumx, sumy;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumx = 0;
            sumy = 0;

            // This is the convolution
            for (int p = -cent; p <= cent; p++)
            {
                for (int q = -cent; q <= cent; q++)
                {
                    if ((i + p) < 0 || (j + q) < 0 || (i + p) >= height || (j + q) >= width)
                        continue;

                    auto row = j + p;
                    auto column = (i + q) * width;
                    sumx += pic[row + column] * maskx[p + cent][q + cent];
                    sumy += pic[row + column] * masky[p + cent][q + cent];
                }
            }

            // Store convolution result in respective matrix
            x[j + i * width] = sumx;
            y[j + i * width] = sumy;
        }
    }

    // Find magnitude and maxVal, then store it in the 'mag' matrix
    double mags;
    double maxVal = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mags = sqrt((x[j + i * width] * x[j + i * width]) + (y[j + i * width] * y[j + i * width]));

            if (mags > maxVal)
                maxVal = mags;

            mag[j + i * width] = mags;
        }
    }

    // Make sure all the magnitude values are between 0-255
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            mag[j + i * width] = mag[j + i * width] / maxVal * 255;

    return;
}

// ================================ Peaks Detection ================================
// The formula for slope is Δy/Δx. We have Δy and Δx from the scanning convulution
// above. We can get the slope by dividing the two. We'll store all the Point2Ds that
// are greater than both it's neighbors in the direction of the slope into a std::vector.
// We can calculate the direction of the slope using the tan(x) function. We'll also
// store the peaks in a HashMap for O(1) searches in the recursiveDT function later.
// ================================ Peaks Detection ================================
std::vector<rstzr::Point2D *> rstzr::peak_detection(std::vector<component_t> &mag, std::map<int, int> &h, double *x,
                                                    double *y, size_t width, size_t height)
{
    std::cout << "peak\n";
    double slope = 0;
    std::vector<rstzr::Point2D *> v;
    std::cout << "peak1\n";

    for (auto i = 1u; i < height - 1; i++)
    {
        for (auto j = 1u; j < width - 1; j++)
        {
            // To avoid dividing by zero
            if (x[j + i * width] == 0)
                x[j + i * width] = 0.0001;

            slope = y[j + i * width] / x[j + i * width];

            // We're only looking for the peaks. If we're at a peak, store 255 in 'peaks'
            if (slope <= tan(22.5) && slope > tan(-22.5))
            {
                /**
                std::cout << "peak2 " << i << ", " << j << "\n";
                std::cout << "\ni1 : " << j + i * width;
                std::cout << "\ni2 : " << i + (j - 1) * width;
                std::cout << "\ni3 : " << i + (j + 1) * width;
                std::cout << "a\n";*/
                if (mag[j + i * width] > mag[j + (i - 1) * width] &&
                    mag[j + (i * width)] > mag[j + (i + 1) * width])
                {
                    std::cout << "p\n";
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
            else if (slope <= tan(67.5) && slope > tan(22.5))
            {
                std::cout << "peak3\n";
                if (mag[j + i * width] > mag[j - 1 + (i - 1) * width] &&
                    mag[j + i * width] > mag[j + 1 + (i + 1) * width])
                {
                    std::cout << "p\n";
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
            else if (slope <= tan(-22.5) && slope > tan(-67.5))
            {
                std::cout << "peak5\n";
                if (mag[j + i * width] > mag[j + 1 + (i - 1) * width] &&
                    mag[j + i * width] > mag[j - 1 + (i + 1) * width])
                {
                    std::cout << "p\n";
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
            else
            {
                std::cout << "peak5\n";
                if (mag[j + i * width] > mag[j - 1 + i * width] &&
                    mag[j + i * width] > mag[j + 1 + i * width])
                {
                    std::cout << "p\n";
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
        }
    }

    return v;
}

// ======================== Hysteresis & Double Thresholding ========================
// The points passed into this function are coming from the peaks vector. We'll start
// by searching around the current pixel for a pixel that made it to "final". If
// found, then we'll recursively search for a "series" of pixels that are in the mid
// range and swith all those to ON in final. We'll stop as soon as all the pixels are
// either already processed or less than the 'lo' threshold.
// ======================== Hysteresis & Double Thresholding ========================
void rstzr::recursiveDT(std::vector<component_t> &mag, component_t *final, std::map<int, int> &h,
                        std::map<int, int> &peaks, int a, int b, int flag, size_t height,
                        size_t width, std::vector<int> &result)
{
    // If the pixel value is < lo, out-of-bounds, or at a point we've visited before,
    // then exit the funciton.
    if (mag[b + a * width] < lo || a < 0 || b < 0 || a >= height || b >= width)
    {
        std::cout << "grr1\n";
        return;
    }
    if (h.find(a) != h.end())
    {
        std::cout << "grr2\n";
        return;
    }

    // Insert the current pixel so we know we've been here before.
    h.insert(std::pair<int, int>(a, b));

    // If flag = 0, that means that this is the first pixel of the "series" that
    // we're looking at. We're going to look for a pixel in "final" that's set to
    // ON. If we found one, assert the flag and break out of the loops.
    if (!flag)
    {
        for (int p = -1; p <= 1; p++)
        {
            for (int q = -1; q <= 1; q++)
            {
                if (final[b + p + (a + q) * width] == 255)
                {
                    final[b + a * width] = 255;
                    result.push_back(b + a * width);
                    flag = 1;
                    std::cout << "a\n";
                    break;
                }
            }

            if (flag)
                break;
        }
    }

    // If flag is asserted, that means we found a pixel that's in final, all what
    // we have to do now is just search for pixels that are in the mid range.
    // Also, make sure that it's in the peaks to begin with.
    if (flag)
    {
        for (int p = -1; p <= 1; p++)
        {
            for (int q = -1; q <= 1; q++)
            {
                if (mag[b + p + (a + q) * width] >= lo && peaks.find(b + p) != peaks.end())
                {
                    recursiveDT(mag, final, h, peaks, a + p, b + q, 1, height, width, result);
                    result.push_back(b + a * width);
                    std::cout << "b\n";
                }
            }
        }
    }

    return;
}

std::vector<int> rstzr::sobel(std::vector<component_t> matrix, size_t width, size_t height)
{
    std::vector<int> result;

    int maskx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int masky[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    auto size = width * height;
    // These matrices will hold the integer values of the input image
    double x[height][width], y[height][width], mag[height][width];

    // Reading in the input image
    std::vector<component_t> pic(size);
    gray(matrix, pic, width, height);

    // mr stands for maskRadius
    // This does the scanning convultion of the masks declared above, and stores
    // the values in the matrices outputx and outputy
    int mr = 1;
    int maxx = 0, maxy = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto sumx = 0;
            auto sumy = 0;

            for (int p = -mr; p <= mr; p++)
            {
                for (int q = -mr; q <= mr; q++)
                {
                    // To make sure we don't go out of bounds
                    if ((i + p) < 0 || (j + q) < 0 || (i + p) >= height || (j + q) >= width)
                        continue;

                    sumx += pic[(i + p * width) + j + q] * maskx[p + mr][q + mr];
                    sumy += pic[(i + p) * width + j + q] * masky[p + mr][q + mr];
                }
            }

            if (sumx > maxx)
                maxx = sumx;
            if (sumy > maxy)
                maxy = sumy;

            x[i][j] = sumx;
            y[i][j] = sumy;
        }
    }

    // Make sure all the values are between 0-255
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            x[i][j] = x[i][j] / maxx * 255;
            y[i][j] = y[i][j] / maxy * 255;
        }
    }

    // Find gradient and maxval
    int maxVal = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mag[i][j] = sqrt((x[i][j] * x[i][j]) + (y[i][j] * y[i][j]));

            if (mag[i][j] > maxVal)
                maxVal = mag[i][j];
        }
    }

    // Make sure all the magnitude values are between 0-255
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            mag[i][j] = mag[i][j] / maxVal * 255;

    // Make sure to cast back to char before outputting
    // Also to avoid any wonky results, get rid of any decimals by casting to int first
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Ouput the high threshold image
            if ((int)mag[i][j] > hi)
                result.push_back(j + i * width);
        }
    }

    return result;
}
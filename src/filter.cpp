#include "filter.h"

#define sig 0.5
#define hi 200
#define lo 50

void rstzr::gray(component_t matrix[], component_t pic[], size_t width, size_t height)
{

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
}

/**
 * Code from: https://github.com/sorazy/canny 
 */
std::vector<int> rstzr::canny(component_t matrix[], size_t width, size_t height)
{
    size_t size = width * height;

    auto pic = new component_t[size];
    gray(matrix, pic, width, height);

    auto mag = new component_t[size];
    auto x = new double[size];
    auto y = new double[size];
    auto final = new component_t[size];

    // Create the magnitute matrix
    magnitude_matrix(pic, mag, x, y, width, height);

    // Get all the peaks and store them in vector
    std::map<int, int> peaks;
    std::vector<Point2D *> v = peak_detection(mag, peaks, x, y, width, height);

    // Go through the vector and call the recursive function and each point. If the value
    // in the mag matrix is hi, then immediately accept it in final. If lo, then immediately
    // reject. If between lo and hi, then check if it's next to a hi pixel using recursion
    std::map<int, int> h;
    int a, b;
    std::vector<int> result;
    for (auto i = 0; i < v.size(); i++)
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

    delete mag;
    delete x;
    delete y;

    return result;
}

void rstzr::magnitude_matrix(component_t pic[], component_t *mag, double *x, double *y,
                             component_t width, component_t height)
{
    int dim = 6 * sig + 1, cent = dim / 2;
    double maskx[dim][dim], masky[dim][dim];

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

                    auto row = i + p;
                    auto column = (j + q) * width;
                    sumx += pic[row + column] * maskx[p + cent][q + cent];
                    sumy += pic[row + column] * masky[p + cent][q + cent];
                }
            }

            // Store convolution result in respective matrix
            x[i + j * width] = sumx;
            y[i + j * width] = sumy;
        }
    }

    // Find magnitude and maxVal, then store it in the 'mag' matrix
    double mags;
    double maxVal = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mags = sqrt((x[i + j * width] * x[i + j * width]) + (y[i + j * width] * y[i + j * width]));

            if (mags > maxVal)
                maxVal = mags;

            mag[i + j * width] = mags;
        }
    }

    // Make sure all the magnitude values are between 0-255
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            mag[i + j * width] = mag[i + j * width] / maxVal * 255;

    return;
}

// ================================ Peaks Detection ================================
// The formula for slope is Δy/Δx. We have Δy and Δx from the scanning convulution
// above. We can get the slope by dividing the two. We'll store all the Point2Ds that
// are greater than both it's neighbors in the direction of the slope into a std::vector.
// We can calculate the direction of the slope using the tan(x) function. We'll also
// store the peaks in a HashMap for O(1) searches in the recursiveDT function later.
// ================================ Peaks Detection ================================
std::vector<rstzr::Point2D *> rstzr::peak_detection(component_t *mag, std::map<int, int> &h, double *x,
                                                    double *y, component_t width, component_t height)
{
    double slope = 0;
    std::vector<rstzr::Point2D *> v;
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // To avoid dividing by zero
            if (x[i + j * width] == 0)
                x[i + j * width] = 0.0001;

            slope = y[i + j * width] / x[i + j * width];

            // We're only looking for the peaks. If we're at a peak, store 255 in 'peaks'
            if (slope <= tan(22.5) && slope > tan(-22.5))
            {
                if (mag[i + j * width] > mag[i + (j - 1) * width] && mag[i + (j * width)] > mag[i + (j + 1) * width])
                {
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
            else if (slope <= tan(67.5) && slope > tan(22.5))
            {
                if (mag[i + j * width] > mag[i - 1 + (j - 1) * width] &&
                    mag[i + j * width] > mag[i + 1 + (j + 1) * width])
                {
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
            else if (slope <= tan(-22.5) && slope > tan(-67.5))
            {
                if (mag[i + j * width] > mag[i + 1 + (j - 1) * width] &&
                    mag[i + j * width] > mag[i - 1 + (j + 1) * width])
                {
                    v.push_back(new Point2D(i, j));
                    h.insert(std::pair<int, int>(i, j));
                }
            }
            else
            {
                if (mag[i + j * width] > mag[i - 1 + j * width] &&
                    mag[i + j * width] > mag[i + 1 + j * width])
                {
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
void rstzr::recursiveDT(component_t mag[], component_t *final, std::map<int, int> &h,
                        std::map<int, int> &peaks, int a, int b, int flag, size_t height,
                        size_t width, std::vector<int> &result)
{
    // If the pixel value is < lo, out-of-bounds, or at a point we've visited before,
    // then exit the funciton.
    if (mag[a + b * width] < lo || a < 0 || b < 0 || a >= height || b >= width)
        return;
    if (h.find(a) != h.end())
        return;

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
                if (final[a + p + (b + q) * width] == 255)
                {
                    final[a + b * width] = 255;
                    result.push_back(a + b * width);
                    flag = 1;
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
                if (mag[a + p + (b + q) * width] >= lo && peaks.find(a + p) != peaks.end())
                {
                    recursiveDT(mag, final, h, peaks, a + p, b + q, 1, height, width, result);
                    result.push_back(a + b * width);
                }
            }
        }
    }

    return;
}
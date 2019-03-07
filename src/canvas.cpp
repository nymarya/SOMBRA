#include "canvas.h"

using component_t = unsigned char;
/**
 * @brief Constructor Default
 */
rstzr::Canvas::Canvas(const size_t width, const size_t height)
    : m_width(width), m_height(height), m_pixels(new component_t[(width * height * 3)]), m_fill_color(Color(0, 0, 0)), m_bkg_color(Color(255, 255, 255))
{

    for (unsigned int x = 0; x < m_width; x++)
    {
        for (unsigned int y = 0; y < m_height; y++)
        {
            pixel(x, y, m_bkg_color);
        }
    }
}

/**
 * @brief Set the color of a pixel on the canvas
 */
//TODO: change x and y to Point2D
void rstzr::Canvas::pixel(const long x, const long y, const Color &c)
{
    // m_pixels[(x*m_width)+y] = c;
    m_pixels[m_width * y + x] = c.red();
    m_pixels[m_height * m_width + m_width * y + x] = c.green();
    m_pixels[m_height * m_width * 2 + m_width * y + x] = c.blue();
}

/**
 * @brief Get the pixel color from canvas
 */
component_t rstzr::Canvas::pixel(const long x, const long y) const
{
    return m_pixels[(x * m_width) + y];
}

/**
 * @brief Get the canvas width
 */
size_t rstzr::Canvas::width(void) const
{
    return m_width;
}

/**
 * @brief Get the canvas height
 */
size_t rstzr::Canvas::height(void) const
{
    return m_height;
}

/**
 * @brief Get the canvas pixels as an array of unsigned char.
 */
component_t *rstzr::Canvas::pixels(void) const
{
    return m_pixels.get();
}

/**
 * @brief Draw a line between two points 2D.
 */
void rstzr::Canvas::line(rstzr::Point2D &p1, rstzr::Point2D &p2, const Color &c, LINE_MODE mode)
{

    //Draw line based on choosen type
    if (mode == LINE_MODE::DDA)
        drawLineDDA(p1, p2, c);
    else if (mode == LINE_MODE::BRESENHAM)
        drawLineBresenham(p1, p2, c);
    else if (mode == LINE_MODE::COMPARE)
    {
        drawLineDDA(p1, p2, Color(0, 0, 255));
        drawLineBresenham(p1, p2, Color(0, 255, 0));
    }
}

/**
 * @brief Draw a circle using the mid-point algorithm
 * @see https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
 */
void rstzr::Canvas::circle(Circle &circle, const Color &c)
{
    //Get the center point
    auto center = circle.center();
    auto x_centre = center.x();
    auto y_centre = center.y();
    auto radius = circle.radius();

    //Get start point
    coord_type x = 0;
    coord_type y = radius;

    // Get the parcial differences (deltas) of L and SE directions
    auto dl = 3;
    auto dse = -2 * radius + 5;
    auto d = 1 - radius;

    pixel(x + x_centre, y + y_centre, c);
    // When radius is zero only a single
    // point will be printed
    if (radius > 0)
    {
        // Color the correspondent pixels
        // in the other octants
        pixel(x + x_centre, -y + y_centre, c);
        pixel(y + x_centre, x + y_centre, c);
        pixel(-y + x_centre, x + y_centre, c);
    }
    while (y > x)
    {
        if (d < 0)
        {
            d += dl;
            dl += 2;
            dse += 2;
        }
        else
        {
            d += dse;
            dl += 2;
            dse += 4;
            y--;
        }

        x++;
        pixel(x + x_centre, y + y_centre, c);
        // Color the correspondent pixels
        // in the other octants
        pixel(-x + x_centre, y + y_centre, c);
        pixel(x + x_centre, -y + y_centre, c);
        pixel(-x + x_centre, -y + y_centre, c);

        // If the generated point is on the line x = y then
        // the perimeter points have already been printed
        if (x != y)
        {
            pixel(y + x_centre, x + y_centre, c);
            pixel(-y + x_centre, x + y_centre, c);
            pixel(y + x_centre, -x + y_centre, c);
            pixel(-y + x_centre, -x + y_centre, c);
        }
    }
}

void rstzr::Canvas::bkg_color(const Color &c)
{
    m_bkg_color = c;
}

void rstzr::Canvas::fill_color(const Color &c)
{
    m_fill_color = c;
}

/**
 * @brief Get the color that will fill the object
 */
rstzr::Color rstzr::Canvas::fill_color() const
{
    return m_fill_color;
}

/**
 * @brief Draw a line between two points 2D
 * @see https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/
 */
void rstzr::Canvas::drawLineDDA(rstzr::Point2D p1, rstzr::Point2D p2, const Color &c)
{
    coord_type x0 = p1.x();
    coord_type x1 = p2.x();
    coord_type y0 = p1.y();
    coord_type y1 = p2.y();

    float dy = y1 - y0;
    float dx = x1 - x0;
    float y = y0;
    float x = x0;

    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    for (int i = 0; i < steps; i++)
    {
        pixel(x, y, c);
        y += y_inc;
        x += x_inc;
    }
}

/**
 * @brief Draw a line between two points 2D using the brsenham algorithm
 * @see https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void rstzr::Canvas::drawLineBresenham(rstzr::Point2D p1, rstzr::Point2D p2, const Color &c)
{
    coord_type x0 = p1.x();
    coord_type x1 = p2.x();
    coord_type y0 = p1.y();
    coord_type y1 = p2.y();

    float dy = y1 - y0;
    float dx = x1 - x0;
    float p;

    // Flag to verify wheter movement m1 is
    // vertical, ie., which axis must be explored
    bool turn = abs(dx) - abs(dy) < 0;

    auto x = x0;
    auto y = y0;
    int i = 1;
    if (!turn)
    {
        //If |dx| >= |dy|, x increases to left
        // and y axis' movements depends on the sign of dy
        // dy >= 0: move up
        // dy < 0 : move down

        i = dy < 0 ? -1 : 1;
        dy = abs(dy);
        p = 2 * dy - 2 * dx;

        for (auto x = x0 + 1; x < x1; x++)
        {
            if (p >= 0)
            {
                y += i;
                p += 2 * abs(dy) - 2 * dx;
            }
            else
            {
                p += 2 * dy;
            }
            pixel(x, y, c);
        }
    }
    else
    {
        //If |dx| < |dy|, y axis always moves up
        // and x axis' move depends on the sign of dx
        // dx >= 0: move to left
        // dx < 0 : move to right

        i = dx < 0 ? -1 : 1;
        dx = abs(dx);
        for (auto y = y0 + 1; y < y1; y++)
        {
            if (p >= 0)
            {
                x += x < x1 ? i : 0;
                p += 2 * dx - 2 * dy;
            }
            else
            {
                p += 2 * dy;
            }
            pixel(x, y, c);
        }
    }
}

void rstzr::Canvas::antiliasing()
{
    // Run edge dectection
    auto copy_pixels = m_pixels.get();
    auto edges = canny(copy_pixels, m_width, m_height);
    for (unsigned int x = 0; x < m_width; x++)
    {
        for (unsigned int y = 0; y < m_height; y++)
        {
            //If pixel is near edge and pixel is near other pixel of your source color,
            //then calculate it’s opacity (1-transparency) factor
            for (unsigned int z = 0; z < 3; z++)
            {
                auto red = m_width * y + x;
                auto green = m_height * m_width + m_width * y + x;
                auto blue = m_height * m_width * 2 + m_width * y + x;

                auto bkg_red = m_bkg_color.red();
                auto bkg_green = m_bkg_color.green();
                auto bkg_blue = m_bkg_color.blue();

                auto opc_red = (m_pixels[red] - bkg_red) / (m_fill_color.red() - bkg_red);
                auto opc_green = (m_pixels[green] - bkg_green) / (m_fill_color.green() - bkg_green);
                auto opc_blue = (m_pixels[blue] - bkg_blue) / (m_fill_color.blue() - bkg_blue);

                //3) Now calculate your color to which you must replace current anti-aliased pixel:
                m_pixels[red] = bkg_red * (1 - opc_red) + opc_red * m_fill_color.red();
                m_pixels[green] = bkg_green * (1 - opc_green) + opc_green * m_fill_color.green();
                m_pixels[blue] = bkg_blue * (1 - opc_blue) + opc_blue * m_fill_color.blue();
            }
        }
    }

    //If pixel is near edge and pixel is near other pixel of your source color,
    //then calculate it’s opacity (1-transparency) factor- which will be
    //opacity = (pixel_color-background_color)/(source_color-background_color)

    //3) Now calculate your color to which you must replace current anti-aliased pixel:

    //new_color = background_color * (1-opacity) + opacity * target_color
    //And put this new_color instead of antialiased pixel.
}
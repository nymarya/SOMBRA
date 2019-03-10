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
 * Checks whether pixel is near edge and pixels is
 * near other pixel of your source color.
 */
bool rstzr::Canvas::check_pixel(size_t x, size_t y, std::vector<int> &edges)
{
    bool check = false;
    // Verify if pixel is near edges
    for (auto i = 0u; (i < edges.size()) & !check; i++)
    {
        if (x + y * m_width == i)
            check = true;
        if ((x + (y + 1 * m_width)) == i)
            check = true;
        if ((x + (y - 1 * m_width)) == i)
            check = true;
        if ((x + 1 + y * m_width) == i)
            check = true;
        if ((x + 1 + (y + 1 * m_width)) == i)
            check = true;
        if ((x + 1 + (y - 1 * m_width)) == i)
            check = true;
        if ((x - 1 + y * m_width) == i)
            check = true;
        if ((x - 1 + (y + 1 * m_width)) == i)
            check = true;
        if ((x - 1 + (y - 1 * m_width)) == i)
            check = true;

        if (check)
        {
            //TODO: change m_fill_color to m_stroke_color
            auto red = m_width * y + x;
            auto green = m_height * m_width + m_width * y + x;
            auto blue = m_height * m_width * 2 + m_width * y + x;

            auto n_green = m_height * m_width + i;
            auto n_blue = m_height * m_width * 2 + i;
            check = check & (m_pixels[red] == m_fill_color.red());
            check = check & (m_pixels[green] == m_fill_color.green());
            check = check & (m_pixels[blue] == m_fill_color.blue());
        }
    }

    if (check)
    {
        //TODO: change m_fill_color to m_stroke_color
        auto red = m_width * y + x;
        auto green = m_height * m_width + m_width * y + x;
        auto blue = m_height * m_width * 2 + m_width * y + x;

        check = check & (m_pixels[red] == m_fill_color.red());
        check = check & (m_pixels[green] == m_fill_color.green());
        check = check & (m_pixels[blue] == m_fill_color.blue());
    }

    return check;
}

void rstzr::Canvas::antiliasing()
{
    // Run edge dectection
    std::cout << "anti\n";
    std::vector<component_t> copy_pixels;
    for (unsigned int x = 0; x < m_width; x++)
    {
        for (unsigned int y = 0; y < m_height; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                auto index = m_height * m_width * z + m_width * y + x;
                copy_pixels.push_back(m_pixels[index]);
            }
        }
    }
    std::cout << "q " << copy_pixels.size();
    auto edges = sobel(copy_pixels, m_width, m_height);
    std::cout << "ed " << edges.size();
    for (unsigned int x = 0; x < m_width; x++)
    {
        for (unsigned int y = 0; y < m_height; y++)
        {
            //If pixel is near edge and pixel is near other pixel of your source color,
            //then calculate it’s opacity (1-transparency) factor
            if (check_pixel(x, y, edges))
            {
                for (unsigned int z = 0; z < 3; z++)
                {
                    auto red = m_width * y + x;
                    auto green = m_height * m_width + m_width * y + x;
                    auto blue = m_height * m_width * 2 + m_width * y + x;

                    auto bkg_red = m_bkg_color.red();
                    auto bkg_green = m_bkg_color.green();
                    auto bkg_blue = m_bkg_color.blue();

                    //TODO: change m_fill_color to m_stroke_color
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
    }

    //If pixel is near edge and pixel is near other pixel of your source color,
    //then calculate it’s opacity (1-transparency) factor- which will be
    //opacity = (pixel_color-background_color)/(source_color-background_color)

    //3) Now calculate your color to which you must replace current anti-aliased pixel:

    //new_color = background_color * (1-opacity) + opacity * target_color
    //And put this new_color instead of antialiased pixel.
}

void rstzr::Canvas::draw(Graphic &g, LINE_MODE mode)
{
    g.draw(*this, mode);
}
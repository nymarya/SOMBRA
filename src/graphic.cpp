#include "graphic.h"

rstzr::Graphic::Graphic(Color &fill, Color &stroke)
    : m_fill_color(fill), m_stroke_color(stroke)
{
    /*empty*/
}

rstzr::Graphic::Graphic(rstzr::Color &stroke)
    : m_stroke_color(stroke)
{
    /*empty*/
}

/**
 * Set the color of the figure.
 */
void rstzr::Graphic::fill_color(const rstzr::Color &c)
{
    m_fill_color = c;
}

/**
     * Get the color of the figure.
     */
rstzr::Color rstzr::Graphic::fill_color() const
{
    return m_fill_color;
}

/**
     * Set the border color.
     */
void rstzr::Graphic::stroke_color(const rstzr::Color &c)
{
    m_stroke_color = c;
}

/**
     * Get the border color.
     */
rstzr::Color rstzr::Graphic::stroke_color() const
{
    return m_stroke_color;
}

/**
     * Set the border width.
     */
void rstzr::Graphic::stroke_width(const int width)
{
    m_stroke_width = width;
}

/**
     * Get the border width.
     */
int rstzr::Graphic::stroke_width() const
{
    return m_stroke_width;
}
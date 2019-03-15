#include "../include/graphic_composite.h"

rstzr::GraphicComposite::GraphicComposite(std::vector<Graphic> &gs)
    : m_graphics(gs)
{
    /*empty*/
}

/**
 * @brief Abstract method for drawing the figure.
 */
void rstzr::GraphicComposite::draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM)
{
    for (auto i = 0u; i < m_graphics.size(); i++)
        m_graphics[i].draw(cv, mode);
}

/**
 * @brief Fill the figure.
 */
void rstzr::GraphicComposite::fill(Canvas &cv)
{
    for (auto i = 0u; i < m_graphics.size(); i++)
        m_graphics[i].fill(cv);
}
#include "../include/graphic_composite.h"

rstzr::GraphicComposite::GraphicComposite(json &j,std::vector<std::unique_ptr<Graphic>> &gs)
    : Graphic(j)
{
    m_graphics = std::move(gs);

    for( auto i=0u; i < m_graphics.size(); i++){
        m_graphics[i]->stroke_color(stroke_color());
        m_graphics[i]->fill_color(fill_color());
    }
}

/**
 * @brief Abstract method for drawing the figure.
 */
void rstzr::GraphicComposite::draw(Canvas &cv, LINE_MODE mode){
    for (auto i = 0u; i < m_graphics.size(); i++){
        m_graphics[i]->draw(cv);
    }
        
}

/**
 * @brief Fill the figure.
 */
void rstzr::GraphicComposite::fill(Canvas &cv)
{
    for (auto i = 0u; i < m_graphics.size(); i++)
        m_graphics[i]->fill(cv);
}
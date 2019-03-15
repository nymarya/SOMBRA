#include "../include/graphic_composite.h"

rstzr::GraphicComposite::GraphicComposite(json &j,std::vector<std::unique_ptr<Graphic>> &gs)
    : Graphic(j)
{
    m_graphics = std::move(gs) ;
}

/**
 * @brief Abstract method for drawing the figure.
 */
void rstzr::GraphicComposite::draw(Canvas &cv, LINE_MODE mode){
    for (auto i = 0u; i < m_graphics.size(); i++){
        std::cout << "g\n";
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
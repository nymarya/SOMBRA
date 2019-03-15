#ifndef _graphic_composite_h_
#define _graphic_composite_h_

#include "graphic.h"
#include "arc.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"

#include <memory>

namespace rstzr
{
/**
 * @brief Class that aggregates multiple objects.
 */
class GraphicComposite : public Graphic
{

  public:
    GraphicComposite(std::vector<Graphic> &gs);
    ~GraphicComposite() = default;

    /**
     * @brief Abstract method for drawing the figure.
     */
    virtual void draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM) = 0;

    /**
     * @brief Fill the figure.
     */
    virtual void fill(Canvas &cv);

  private:
    std::vector<Graphic> m_graphics;
};

} // namespace rstzr

#endif
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
    GraphicComposite(json &j, std::vector<std::unique_ptr<Graphic>> &gs);
    ~GraphicComposite() = default;

    /**
     * @brief Method for drawing the figure.
     */
    void draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM);

    /**
     * @brief Fill the figure.
     */
    void fill(Canvas &cv);

  private:
    std::vector<std::unique_ptr<Graphic>> m_graphics;
};

} // namespace rstzr

#endif
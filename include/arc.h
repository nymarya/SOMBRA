#ifndef _arc_h_
#define _arc_h_

#include "point.h"
#include "graphic.h"
#include "common.h"
#include "canvas.h"

#define PI 3.14159265

namespace rstzr
{
class Arc : public Graphic
{

  public:
    Arc(Point2D center, int start_angle, int end_angle, int radius, Color stroke);
    ~Arc() = default;

    void draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM);

  private:
    Point2D m_center; //start point
    int m_start_angle, m_end_angle, m_radius;
};
} // namespace rstzr

#endif
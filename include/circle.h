#ifndef _circle_h_
#define _circle_h_

#include "point.h"
#include "graphic.h"
#include "canvas.h"

namespace rstzr
{

class Circle : public Graphic
{

public:
  Circle(int radius, Point2D center, Color &stroke);
  Circle(int radius, Point2D center, Color &fill, Color &stroke);
  ~Circle() = default;

  /**
     * @brief Get the radius of the circle
     */
  int radius() const;

  /**
     * @brief Get the center of the circle.
     */
  Point2D center() const;

  void draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM);

private:
  int m_radius;

  Point2D m_center;
}; //class Circle

} // namespace rstzr

#endif
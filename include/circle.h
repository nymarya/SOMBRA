#ifndef _circle_h_
#define _circle_h_

#include "point.h"
namespace rstzr
{

class Circle
{

  public:
    Circle(int radius, Point2D center);
    ~Circle() = default;

    /**
     * @brief Get the radius of the circle
     */
    int radius() const;

    /**
     * @brief Get the center of the circle.
     */
    Point2D center() const;

  private:
    int m_radius;

    Point2D m_center;
}; //class Circle

} // namespace rstzr

#endif
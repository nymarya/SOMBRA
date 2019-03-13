#ifndef _circle_h_
#define _circle_h_

#include "point.h"
#include "arc.h"

namespace rstzr
{

class Circle : public Arc
{

public:
  /**
   * @brief Create circle based on json file
   */
  Circle(json &j);

  ~Circle() = default;

   /**
   * @brief Fill the figure using the boundary fill method.
   */
   void fill(Canvas &cv) ;

private:
  /**
   * @brief Fill object using the boundary fill method
   */
   void boundary_fill(Canvas &cv, const Point2D &p, const Color &fill, const Color &boundary);
}; //class Circle

} // namespace rstzr

#endif
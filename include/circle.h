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

private:
}; //class Circle

} // namespace rstzr

#endif
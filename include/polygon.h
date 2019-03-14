#ifndef _polygon_h_
#define _polygon_h_

#include "graphic.h"
#include "line.h"

namespace rstzr
{

class Polygon : public Graphic
{
public:
  /**
   * @brief Constructs a polygon based on a json object
   */
  Polygon(json &j);

  /**
   * @brief Default destructor
   */
  ~Polygon() = default;

  /**
	 * @brief Draw all lines in a canvas.
	 */
  void draw(Canvas &cv, LINE_MODE mode);

private:
  /* data */
  std::vector<Line> m_lines;
};

} // namespace rstzr

#endif
#ifndef _polygon_h_
#define _polygon_h_

#include "graphic.h"
#include "line.h"


#include <typeinfo>

namespace rstzr
{
/**
 * @brief Class that represents a polygon.
 */
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

  /**
   * @brief Fill the figure using the scan-line method.
   */
  void fill(Canvas &cv) override;

  /**
   * @brief Get the global edges ordered by their smallest y coordinate.
   */
  std::vector<std::vector<float>> ET();

private:
  /* data */
  std::vector<Line> m_lines;

  // bool compare_aet( std::vector<float> v1, std::vector<float> v2);
};

} // namespace rstzr

#endif
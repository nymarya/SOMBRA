#ifndef _line_h_
#define _line_h_

#include <vector>

#include "color.h"
#include "point.h"
#include "graphic.h"
#include "canvas.h"

namespace rstzr
{

/**
 * @brief Class that represents a line
 */
class Line : public Graphic
{
  public:
	/**
	 * @brief Constructor for class Line based on json.
	 */
	Line(json &j);
	/**
	 * @brief Constructor for class Line.
	 */
	Line(Point2D p1, Point2D p2, Color &c);

	/**
	 * @brief Destructor 
	 */
	~Line() = default;

	/**
	 * @brief Draw a line between two points 2D
	 */
	void drawDDA(Canvas &cv);

	/**
	 * @brief Draw a line between two points 2D using the brsenham algorithm
	 */
	void drawBresenham(Canvas &cv);

	/**
	 * @brief Draw a line in a canvas.
	 */
	void draw(Canvas &cv, LINE_MODE mode);

	/**
	 * @brief Get the data needed for a ET bucket (y_max, x_min, 1/m)
	 */
	int* to_bucket();

  private:
	Point2D m_p1;
	Point2D m_p2;

	coord_type y_max;
	coord_type x_min;
	float slope; //dx/dy
};
} // namespace rstzr

#endif
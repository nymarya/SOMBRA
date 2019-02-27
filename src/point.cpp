#include "../include/point.h"

/**
 * @brief Contructor for point object
 * @param x X coordinate.
 * @param y Y coordinate.
 */
rstzr::Point2D::Point2D(coord_type x, coord_type y)
	: m_x(x), m_y(y)
{ /*empty*/
}

/**
 * @brief Return the x-coordinate.
 */
coord_type rstzr::Point2D::x() const
{
	return m_x;
}

/**
 * @brief Return the y-coordinate.
 */
coord_type rstzr::Point2D::y() const
{
	return m_y;
}
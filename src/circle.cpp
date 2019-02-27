#include "../include/circle.h"

rstzr::Circle::Circle(int radius, Point2D center)
    : m_radius(radius), m_center(center)
{ /*empty*/
}

/**
 * @brief Get the radius of the circle
 */
int rstzr::Circle::radius() const
{
    return m_radius;
}

/**
 * @brief Get the center of the circle.
 */
rstzr::Point2D rstzr::Circle::center() const
{
    return m_center;
}
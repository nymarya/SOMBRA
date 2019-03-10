#include "../include/circle.h"

rstzr::Circle::Circle(int radius, Point2D center, Color &stroke)
    : m_radius(radius), m_center(center), Graphic(stroke)
{ /*empty*/
}

rstzr::Circle::Circle(int radius, Point2D center, Color &fill, Color &stroke)
    : m_radius(radius), m_center(center), Graphic(fill, stroke)
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

/**
 * @brief Draw a circle using the mid-point algorithm
 * @see https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
 */
void rstzr::Circle::draw(Canvas &cv, LINE_MODE mode)
{
    //Get the center point
    auto x_centre = m_center.x();
    auto y_centre = m_center.y();
    auto radius = m_radius;

    //Get start point
    coord_type x = 0;
    coord_type y = radius;

    // Get the parcial differences (deltas) of L and SE directions
    auto dl = 3;
    auto dse = -2 * radius + 5;
    auto d = 1 - radius;

    Color c = stroke_color();

    cv.pixel(x + x_centre, y + y_centre, stroke_color());
    // When radius is zero only a single
    // point will be printed
    if (radius > 0)
    {
        // Color the correspondent pixels
        // in the other octants
        cv.pixel(x + x_centre, -y + y_centre, c);
        cv.pixel(y + x_centre, x + y_centre, c);
        cv.pixel(-y + x_centre, x + y_centre, c);
    }
    while (y > x)
    {
        if (d < 0)
        {
            d += dl;
            dl += 2;
            dse += 2;
        }
        else
        {
            d += dse;
            dl += 2;
            dse += 4;
            y--;
        }

        x++;

        cv.pixel(x + x_centre, y + y_centre, c);
        // Color the correspondent pixels
        // in the other octants
        cv.pixel(-x + x_centre, y + y_centre, c);
        cv.pixel(x + x_centre, -y + y_centre, c);
        cv.pixel(-x + x_centre, -y + y_centre, c);

        // If the generated point is on the line x = y then
        // the perimeter points have already been printed
        if (x != y)
        {
            cv.pixel(y + x_centre, x + y_centre, c);
            cv.pixel(-y + x_centre, x + y_centre, c);
            cv.pixel(y + x_centre, -x + y_centre, c);
            cv.pixel(-y + x_centre, -x + y_centre, c);
        }
    }
}
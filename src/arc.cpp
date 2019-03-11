#include "arc.h"

rstzr::Arc::Arc(Point2D center, int start_angle, int end_angle, int radius, Color stroke)
    : m_center(center), m_start_angle(start_angle), m_end_angle(end_angle),
      m_radius(radius), Graphic(stroke)
{ /*empty*/
}

void rstzr::Arc::draw(Canvas &cv, LINE_MODE mode)
{
    //Get the center point
    auto x_centre = m_center.x();
    auto y_centre = m_center.y();
    auto radius = m_radius;

    //Get start point
    coord_type x = radius * cos(m_start_angle);
    coord_type y = radius * sin(m_start_angle);

    //Get end point
    coord_type end_x = radius * cos(m_end_angle);
    coord_type end_y = radius * sin(m_end_angle);

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
    while (y > end_y & x > end_x)
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
        if (m_end_angle + m_start_angle == 360)
        {
            cv.pixel(-x + x_centre, y + y_centre, c);
            cv.pixel(x + x_centre, -y + y_centre, c);
            cv.pixel(-x + x_centre, -y + y_centre, c);
        }

        // If the generated point is on the line x = y then
        // the perimeter points have already been printed
        if (x != y)
        {
            cv.pixel(y + x_centre, x + y_centre, c);
            if (m_end_angle + m_start_angle == 360)
            {
                cv.pixel(-y + x_centre, x + y_centre, c);
                cv.pixel(y + x_centre, -x + y_centre, c);
                cv.pixel(-y + x_centre, -x + y_centre, c);
            }
        }
    }
}
#include "arc.h"

rstzr::Arc::Arc(json &j)
    : Graphic(j)
{
    m_center = Point2D(j.at("center")[0], j.at("center")[1]);
    m_radius = j.at("radius");
    m_start_angle = j.at("start_angle");
    m_end_angle = j.at("end_angle");
}

rstzr::Arc::Arc(json &j, int start_angle, int end_angle)
    : m_center(Point2D(j.at("center")[0], j.at("center")[1])), m_radius(j.at("radius")),
      m_start_angle(start_angle), m_end_angle(end_angle), Graphic(j)
{
    //empty
}

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
    coord_type x = radius * cos(m_start_angle * PI / 180.0);
    coord_type y = radius * sin(m_start_angle * PI / 180.0);

    //Get end point
    coord_type end_x = radius * sin(m_end_angle * PI / 180.0);
    coord_type end_y = radius * cos(m_end_angle * PI / 180.0);

    // Get the parcial differences (deltas) of L and SE directions
    auto dl = 3;
    auto dse = -2 * radius + 5;
    auto d = 1 - radius;

    Color c = stroke_color();
    auto angle = atan2(y, x) * 180 / PI;

    cv.pixel(x + x_centre, y + y_centre, stroke_color());
    // When radius is zero only a single
    // point will be printed

    if (radius > 0)
    {
        // Color the correspondent pixels
        // in the other octants
        // draw point in range 45 to 90
        //cv.pixel(x + x_centre, -y + y_centre, c);
        //cv.pixel(y + x_centre, x + y_centre, c);
        //cv.pixel(-y + x_centre, x + y_centre, c);
    }
    while ((y > x))
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

        angle = atan2(y, x) * 180 / PI;

        // draw point in range 0 to 45 degrees
        if (angle >= m_end_angle && angle <= m_start_angle && (0 <= angle && angle <= 45))
            cv.pixel(x + x_centre, y + y_centre, c);

        // Color the correspondent pixels
        // in the other octants

        //// draw point in range 135 to 180 degrees
        if (angle >= m_end_angle && angle <= m_start_angle && (135 <= angle && angle <= 180))
            cv.pixel(-x + x_centre, y + y_centre, c);

        // draw point in range 180 to 225 degrees
        if (angle >= m_end_angle && angle <= m_start_angle && (180 <= angle && angle <= 225))
            cv.pixel(-x + x_centre, -y + y_centre, c);

        // draw point in range 315 to 360 degrees
        if (angle >= m_end_angle && angle <= m_start_angle && (315 <= angle && angle <= 360))
            cv.pixel(x + x_centre, -y + y_centre, c);

        // If the generated point is on the line x = y then
        // the perimeter points have already been printed
        if (x != y)
        {

            //// draw point in range 45 to 90 degrees
            if ((m_end_angle <= angle && angle <= m_start_angle) && (45 <= angle && angle <= 90))
                cv.pixel(y + x_centre, x + y_centre, c);

            //// draw point in range 90 to 135 degrees
            //std::cout << "a : " << angle << " .. " << atan (abs(x/y)) * 180.0 / PI << "\n";
            if ((m_end_angle <= angle && angle <= m_start_angle) && (90 <= angle && angle <= 135))
                cv.pixel(-y + x_centre, x + y_centre, c);

            // draw point in range 225 to 270 degrees
            if (angle >= m_end_angle && angle <= m_start_angle && (225 <= angle && angle <= 270))
                cv.pixel(-y + x_centre, -x + y_centre, c);

            // draw point in range 270 to 315 degrees
            if (angle >= m_end_angle && angle <= m_start_angle && (270 <= angle && angle <= 315))
                cv.pixel(y + x_centre, -x + y_centre, c);
        }
    }
}

/**
 * @brief Get radius.
 */
int rstzr::Arc::radius()
{
    return m_radius;
}
#include "arc.h"

rstzr::Arc::Arc(Point2D center, int start_angle, int end_angle, int radius, Color stroke)
    : m_center(center), m_start_angle(start_angle), m_end_angle(end_angle),
      m_radius(radius), Graphic(stroke)
{ /*empty*/
}

void rstzr::Arc::draw(Canvas &cv, LINE_MODE mode)
{
    std::cout << "aa\n";
    //Get the center point
    auto x_centre = m_center.x();
    auto y_centre = m_center.y();
    auto radius = m_radius;

    //Get start point
    coord_type x = radius * cos(m_start_angle * PI / 180.0 );
    coord_type y = radius * sin(m_start_angle * PI / 180.0 );

    //Get end point
    coord_type end_x = radius * sin(m_end_angle * PI / 180.0);
    coord_type end_y = radius * cos(m_end_angle * PI / 180.0);

    // Get the parcial differences (deltas) of L and SE directions
    auto dl = 3;
    auto dse = -2 * radius + 5;
    auto d = 1 - radius;

    Color c = stroke_color();
    auto angle = atan2 (y,x) * 180 / PI;
    std::cout << "a: " << angle << "\n";
    std::cout << "de <" << x << "+ " <<x_centre << ", " << y <<"+"<< y_centre<< ">\n";

    std::cout << "de <" << end_x << "+ " <<x_centre << ", " << end_y <<"+"<< y_centre<< ">\n";
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
    while ( (y > x) | (angle > m_end_angle))
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

        angle = atan2 (y,x) * 180 / PI;
        std::cout << "a " << angle << ">\n";
        std::cout << "<" << x+x_centre << ", " << y+y_centre << ">\n";
        
        
        cv.pixel(x + x_centre, y + y_centre, c);
        /**
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
        }**/
    }
}
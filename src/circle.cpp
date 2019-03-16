#include "../include/circle.h"

/**
 * @brief Create circle based on json file
 */
rstzr::Circle::Circle(json &j)
    : Arc(j, 360, 0)
{
}

/**
 * @brief Fill the figure using the boundary fill method.
 */
void rstzr::Circle::fill(Canvas &cv)
{
    //if (fill_mode() != FILL_MODE::NONE)
        //boundary_fill(cv, centre(), fill_color(), stroke_color());
}

/**
 * @brief Fill object using the boundary fill method
 */
void rstzr::Circle::boundary_fill(Canvas &cv, const rstzr::Point2D &p, const rstzr::Color &fill, const rstzr::Color &boundary)
{
    auto x = p.x();
    auto y = p.y();
    
    if (x < 0 || x > cv.width()-1 )
        return;
    if (y < 0 || y > cv.height()-1 )
        return;
    Color current = cv.color(x, y);
    if (!(current == boundary) & !(current == fill))
    {
        cv.pixel(x, y, fill);
        boundary_fill(cv, Point2D(x + 1, y), fill, boundary);
        boundary_fill(cv, Point2D(x, y + 1), fill, boundary);
        boundary_fill(cv, Point2D(x - 1, y), fill, boundary);
        boundary_fill(cv, Point2D(x, y - 1), fill, boundary);
    }
}

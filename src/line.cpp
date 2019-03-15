
#include <iostream>
#include "../include/line.h"

/**
 * @brief Constructor for class Line.
 */
rstzr::Line::Line(json &j)
    : m_p1(Point2D(j.at("p1")[0], j.at("p1")[1])), m_p2(Point2D(j.at("p2")[0], j.at("p2")[1])),
      Graphic(j)
{ /*empty*/
}

/**
 * @brief Constructor for class Line.
 */
rstzr::Line::Line(Point2D p1, Point2D p2, Color &stroke)
    : m_p1(p1), m_p2(p2), Graphic(stroke)
{ /*empty*/
}

/**
 * @brief Draw a line between two points 2D
 * @see https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/
 */
void rstzr::Line::drawDDA(Canvas &c)
{
    std::cout << " dda\n";
    coord_type x0 = m_p1.x();
    coord_type x1 = m_p2.x();
    coord_type y0 = m_p1.y();
    coord_type y1 = m_p2.y();

    float dy = y1 - y0;
    float dx = x1 - x0;
    float y = y0;
    float x = x0;

    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    for (int i = 0; i < steps; i++)
    {
        c.pixel(x, y, stroke_color());
        y += y_inc;
        x += x_inc;
    }
}

/**
 * @brief Draw a line between two points 2D using the brsenham algorithm
 * @see https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void rstzr::Line::drawBresenham(Canvas &c)
{
    coord_type x0 = m_p1.x();
    coord_type x1 = m_p2.x();
    coord_type y0 = m_p1.y();
    coord_type y1 = m_p2.y();

    float dy = y1 - y0;
    float dx = x1 - x0;
    float p = 0.0;

    // Flag to verify wheter movement m1 is
    // vertical, ie., which axis must be explored
    bool turn = abs(dx) < abs(dy);

    auto x = x0;
    auto y = y0;
    int i = 1;
    if (!turn)
    {
        //If |dx| >= |dy|, x increases to left
        // and y axis' movements depends on the sign of dy
        // dy >= 0: move up
        // dy < 0 : move down

        if (dy < 0)
            i = -1;
        else if (dy == 0)
            i = 0;
        else
            i = 1;
        p = 2 * dy - 2 * dx;

        for (auto x = x0 + 1; x <= x1; x++)
        {
            if (p >= 0)
            {
                y += i;
                p += 2 * dy - 2 * dx;
            }
            else
            {
                p += 2 * dy;
            }
            c.pixel(x, y, stroke_color());
        }
    }
    else
    {
        //If |dx| < |dy|, y axis always moves up
        // and x axis' move depends on the sign of dx
        // dx >= 0: move to left
        // dx < 0 : move to right

        if (dx < 0)
        {
            i = -1;
            dx = -dx;
        }
        else if (dx == 0)
            i = 0;
        else
            i = 1;

        p = 2 * dx - 2 * dy;
        for (auto y = y0 + 1; y <= y1; y++)
        {
            if (p >= 0)
            {
                x += i;
                p += 2 * dx - 2 * dy;
            }
            else
            {
                p += 2 * dx;
            }
            c.pixel(x, y, stroke_color());
        }
    }
}

/**
 * @brief Draw a line between two points 2D.
 */
void rstzr::Line::draw(Canvas &cv, LINE_MODE mode)
{

    //Draw line based on choosen type
    if (mode == LINE_MODE::DDA)
        drawDDA(cv);
    else if (mode == LINE_MODE::BRESENHAM)
        drawBresenham(cv);
    else if (mode == LINE_MODE::COMPARE)
    {
        drawDDA(cv);
        drawBresenham(cv);
    }
}

/**
 * @brief Get the data needed for a ET bucket (y_max, x_min, 1/m)
 */
float *rstzr::Line::to_bucket()
{
    auto bucket = new float[4];

    float x1 = m_p1.x();
    float y1 = m_p1.y();
    float x2 = m_p2.x();
    float y2 = m_p2.y();

    auto y_max = 0;
    auto y_min = 0;

    if (y1 < y2)
    {
        y_max = y2;
        y_min = y1;
    }
    else
    {
        y_max = y1;
        y_min = y2;
    }

    auto x_min = x1 > x2 ? x2 : x1;

    // dx/dy
    float m_inverse = (y2 - y1) == 0 ? 0.0:  (x2 - x1) / (y2 - y1);

    bucket[0] = y_max;
    bucket[1] = x_min;
    bucket[2] = m_inverse;
    bucket[3] = y_min;

    return bucket;
}

/**
 * @brief Get the first point.
 */
rstzr::Point2D rstzr::Line::p1(){
    return m_p1;
}

/**
 * @brief Get the second point.
 */
rstzr::Point2D rstzr::Line::p2(){
    return m_p2;
}

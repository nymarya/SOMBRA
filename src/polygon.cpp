#include "../include/polygon.h"

/**
 * @brief Constructs a polygon based on a json object
 */
rstzr::Polygon::Polygon(json &j)
    : Graphic(j)
{
    std::vector<Line> vec;
    m_lines = vec;
    auto points = j.at("points");
    Color c = stroke_color();

    for (auto i = 0u; i < points.size() - 1; i += 2)
    {
        auto x0 = points[i][0];
        auto x1 = points[i + 1][0];
        auto y0 = points[i][1];
        auto y1 = points[i + 1][1];

        if (y0 <= y1)
        {
            Line line(Point2D(x0, y0), Point2D(x1, y1), c);
            m_lines.push_back(line);
        }
        else
        {
            Line line(Point2D(x1, y1), Point2D(x0, y0), c);
            m_lines.push_back(line);
        }
    }
}

/**
 * @brief Draw all lines in a canvas.
 */
void rstzr::Polygon::draw(Canvas &cv, LINE_MODE mode)
{
    for (auto line : m_lines)
        line.draw(cv, mode);
}
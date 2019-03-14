#include "../include/polygon.h"

/**
 * @brief Constructs a polygon based on a json object
 */
rstzr::Polygon::Polygon(json &j)
    : Graphic(j), m_lines(std::vector<Line>(100))
{
    auto points = j.at("points");
    for (auto i = 0u; i < points.size() - 1; i++)
    {
        Line line(Point2D(points[i][0], points[i][1]), Point2D(points[i + 1][0], points[i + 1][1]));
        m_lines.push_back(line);
    }
}
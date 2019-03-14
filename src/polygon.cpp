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
    std::cout << "aab " <<points.size() <<"\n";
    std::cout << points << "\n";
    for (auto i = 0u; i < points.size()-1; i += 2)
    {
        std::cout << "i: " << i << " " << points[i].size() <<"\n";
        auto x0 = points[i][0];
        std::cout << "x : " << x0 << "\n";
        auto x1 = points[i + 1][0];
        std::cout << "x1 : " << x1 << "\n";
        auto y0 = points[i][1];
        std::cout << "y : " << y0 << "\n";
        auto y1 = points[i + 1][1];
        std::cout << "y1 : " << y1 << "\n";
        
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

    std::cout << "end";
}

/**
 * @brief Draw all lines in a canvas.
 */
void rstzr::Polygon::draw(Canvas &cv, LINE_MODE mode)
{
    std::cout << "p/n";
    for (auto line : m_lines)
        line.draw(cv, mode);
}
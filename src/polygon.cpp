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

/**
 * @brief Fill the figure using the scan-line method.
 */
void rstzr::Polygon::fill(Canvas &cv)
{
    // Get ET

    // Get the smallest y that has an entry in ET

    // Init AET 

    // Repeats until both AET and ET are empty

        // Move to AET the edges that are minimal (y=y_min)

        // Order AET based on the x value

        // Preencha pixels da scan-line y usando pares de x de 
        // arestas consecutivas de AET

        // Remova de AET aquelas arestas y = y max

        // Get next scan-line (y++)

        //  Para cada aresta não vertical de AET, atualize x para o
        // novo y (usar algoritmo incremental)
}

/**
 * @brief Get the global edges ordered by their smallest y coordinate.
 */
std::vector< std::vector<int>> rstzr::Polygon::EAT(){

    auto n = m_lines.size();

    std::vector<std::vector<int>> edges(n);

    // Save the edges with the expected structure for a bucket
    //  _____________________
    // | y_max | x_min | 1/m |
    // |_______|_______|_____|
    for( auto i=0u; i < edges.size(); i++){
        edges[i][0]= m_lines[i].to_bucket()[0];
        edges[i][1]= m_lines[i].to_bucket()[1];
        edges[i][2]= m_lines[i].to_bucket()[2];
    }
        
    // Sort using the bucket sort
    // @see https://www.geeksforgeeks.org/bucket-sort-2/

    // 1) Create n empty buckets 
    std::vector<std::vector<std::vector<int>>> b(n); 
     
    // 2) Put array elements in different buckets 
    for (auto i=0u; i<n; i++) 
    { 
       int bi = n*m_lines[i].to_bucket()[3]; // Index in bucket 
       b[bi].push_back(edges[i]); 
    } 
  
    // 3) Sort individual buckets 
    for (auto i=0u; i<n; i++) 
       std::sort(b[i].begin(), b[i].end()); 
  
    // 4) Concatenate all buckets into arr[] 
    int index = 0; 
    for (auto i = 0u; i < n; i++) 
        for (auto j = 0u; j < b[i].size(); j++) 
          edges[index++] = b[i][j];

    return edges;
}
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

        if ((y0 <= y1) || (x0 <= x1))
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
 * @brief Comparator function to sort aet by x.
 */
bool compare_aet( std::vector<float> v1, std::vector<float> v2){
    return v1[1] < v2[1];
}

/**
 * @brief Fill the figure using the scan-line method.
 */
void rstzr::Polygon::fill(Canvas &cv)
{
    // Get ET
    auto et = ET();

    // Get the smallest y that has an entry in ET
    auto y_min = et[0][0];
    for (auto i = 0u; i < et.size(); i++)
    {
        for (auto j = 0u; j < et[i].size(); j++)
        {
            y_min = (y_min > et[i][j])? et[i][j] : y_min;
        }
    }

    // Init AET
    std::vector<std::vector<float>> aet;

    auto y_current = 0;

    // Repeats until both AET and ET are empty
    while(!aet.empty() || !et.empty() ){
        // Move to AET the edges that are minimal (y=y_min)
        for( auto i=0u; i< m_lines.size(); i++){
            auto line = m_lines[i];
            auto bucket = line.to_bucket();
            if( (bucket[3] == y_min) ){
                aet[i][0] = bucket[0];
                aet[i][1] = bucket[1];
                aet[i][2] = bucket[2];
            }
        }

        // Order AET based on the x value
        std::sort (aet.begin(), aet.begin(), compare_aet);

        // Preencha pixels da scan-line y usando pares de x de
        // arestas consecutivas de AET
        for( auto i=0u; i < aet.size(); i++){
            auto x = aet[i][1];
            auto dx = abs(aet[i][4]);
            while( dx >= 0 )
                cv.pixel(x + dx--, y_current, fill_color());
        }

        // Remova de AET aquelas arestas y = y max
        std::vector<size_t> to_drop;
        for( auto i=0u; i < aet.size(); i++){
            if(aet[i][0] == y_current)
                to_drop.push_back(i);
        }
        for( auto i=0u; i< to_drop.size(); i++)
            aet.erase(aet.begin() + to_drop[i]);
            
        // Get next scan-line
        y_current++;

        //  Para cada aresta não vertical de AET, atualize x para o
        // novo y (usar algoritmo incremental)
        for( auto i=0u; i < aet.size(); i++)
            aet[i][1] = y_current;
        
    }
    
}

/**
 * @brief Get the global edges ordered by their smallest y coordinate.
 */
std::vector<std::vector<float>> rstzr::Polygon::ET()
{

    auto n = m_lines.size();

    std::vector<std::vector<float>> edges(n);

    // Save the edges with the expected structure for a bucket
    //  _____________________________
    // |       |       |     |       |
    // | y_max | x_min | 1/m | y_min |
    // |_______|_______|_____|_______|
    for (auto i = 0u; i < edges.size(); i++)
    {
        edges[i] = {0.0, 0.0, 0.0, 0.0};
        edges[i][0] = m_lines[i].to_bucket()[0];
        edges[i][1] = m_lines[i].to_bucket()[1];
        edges[i][2] = m_lines[i].to_bucket()[2];
        edges[i][3] = m_lines[i].to_bucket()[3];
    }

    // Sort using the bucket sort
    // @see https://www.geeksforgeeks.org/bucket-sort-2/

    // 1) Create n empty buckets
    std::vector<std::vector<std::vector<float>>> b(n);

    // 2) Put array elements in different buckets
    for (auto i = 0u; i < n; i++)
    {
        int bi = (int)m_lines[i].to_bucket()[3] % n; // Index in bucket
        b[bi].push_back(edges[i]);
    }

    // 3) Sort individual buckets
    for (auto i = 0u; i < n; i++)
        std::sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (auto i = 0u; i < n; i++)
        for (auto j = 0u; j < b[i].size(); j++)
            edges[index++] = b[i][j];

    return edges;
}
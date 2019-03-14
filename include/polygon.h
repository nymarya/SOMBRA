#ifndef _polygon_h_
#define _polygon_h_

#include "graphic.h"
#include "line.h"

namespace rstzr
{

class Polygon : public Graphic
{
  public:
    /**
             * @brief Constructs a polygon based on a json object
             */
    Polygon(json &j);

    /**
             * @brief Default destructor
             */
    ~Polygon() = default;

  private:
    /* data */
    std::vector<Line> m_lines;
};

} // namespace rstzr

#endif
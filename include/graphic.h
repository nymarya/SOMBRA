#ifndef _graphic_h_
#define _graphic_h_

#include "color.h"

namespace rstzr
{

class Graphic
{

  public:
    Graphic(/* args */);
    ~Graphic();

  private:
    /* data */
    Color m_fill_color, m_background_color, m_stroke_color;
};

} // namespace rstzr

#endif
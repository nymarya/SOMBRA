#ifndef _graphic_h_
#define _graphic_h_

#include "color.h"
#include "common.h"
#include "json.hpp"

using json = nlohmann::json;

namespace rstzr
{

class Canvas;

class Graphic
{

 public:
   /**
   * @brief Construct graphic based on json file
   */
   Graphic(json &j);

   Graphic(Color &stroke);
   Graphic(Color &fill, Color &stroke);
   ~Graphic() = default;

   /**
     * Set the color of the figure.
     */
   void fill_color(const Color &c);

   /**
     * Get the color of the figure.
     */
   Color fill_color() const;

   /**
     * Set the border color.
     */
   void stroke_color(const Color &c);

   /**
     * Get the border color.
     */
   Color stroke_color() const;

   /**
     * Set the border width.
     */
   void stroke_width(const int width);

   /**
     * Get the border width.
     */
   int stroke_width() const;

   virtual void draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM) = 0;

 private:
   /* data */
   Color m_stroke_color, m_fill_color;
   int m_stroke_width;
};

} // namespace rstzr

#endif
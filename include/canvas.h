#ifndef _canvas_h_
#define _canvas_h_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <math.h>

#include "color.h"
#include "point.h"
#include "graphic.h"

#include "filter.h"

using component_t = unsigned char;

namespace rstzr
{

class Canvas
{

 public:
   /**
   * @brief Constructor Default
   */

   Canvas() = default;
   Canvas(std::size_t width, std::size_t height);

   /**
    *@brief Copy constructor.
    */
   Canvas &operator=(Canvas &other);

   /**
             * @brief  Destructor default
             */
   ~Canvas() = default;

   /**
             * @brief Set the color of a pixel on the canvas
             */
   void pixel(const long x, const long y, const Color &c);

   /**
     * @brief Get the pixel color from canvas
     */
   component_t pixel(const long x, const long y) const;

    /**
     * @brief Get the color of a pixel from canvas
     */
   Color color(const long x, const long y) const;

   /**
     * @brief Get the canvas' width
     */
   size_t width(void) const;

   /**
     * @brief Get the canvas' width
     */
   void width(const size_t);

   /**
     * @brief Get the canvas' height
     */
   size_t height(void) const;

   /**
     * @brief Get the canvas' height
     */
   void height(const size_t);

   /**
     * @brief Get the canvas pixels as an array of unsigned char.
     */
   component_t *pixels(void) const;

   /**
     * @brief Draw a line between two points 2D
     */
   void line(rstzr::Point2D &p1, rstzr::Point2D &p2, const Color &c, LINE_MODE mode);

   void bkg_color(const Color &c);

   void fill_color(const Color &c);

   /**
     * @brief Get the color that will fill the object
     */
   Color fill_color() const;

   /**
    * @brief Set the color that will draw the object.
    */
   void stroke_color(const Color &c);

   /**
     * @brief Get the color that will draw the object
     */
   Color stroke_color() const;

   void draw(Graphic &g, LINE_MODE mode = LINE_MODE::BRESENHAM);
   /**
   * Checks whether pixel is near edge and pixels is
   * near other pixel of your source color.
   */
   bool check_pixel(size_t x, size_t y, std::vector<int> &edges);

   void antiliasing();

   /**
   * @brief Fill object using the boundary fill method
   */
   void boundary_fill(const Point2D &p, const Color &fill, const Color &boundary);

 private:
   size_t m_width;

   size_t m_height;

   //n x m x 3
   std::unique_ptr<component_t[]> m_pixels;

   Color m_fill_color, m_stroke_color;

   Color m_bkg_color;
};

} // namespace rstzr

#endif
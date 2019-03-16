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
     * @brief Set the color of the figure.
     */
  void fill_color(const Color &c);

  /**
     * @brief Get the color of the figure.
     */
  Color fill_color() const;

  /**
     * @brief Set the border color.
     */
  void stroke_color(const Color &c);

  /**
     * @brief Get the border color.
     */
  Color stroke_color() const;

  /**
     * @brief Set the border width.
     */
  void stroke_width(const int width);

  /**
     * @brief Get the border width.
     */
  int stroke_width() const;

  /**
   * @brief Set the fill mode of the figure (boundary, scan-line or none)
   */
  void fill_mode(FILL_MODE mode);

  /**
     * @brief Get the fill mode of the figure (boundary, scan-line or none)
     */
  FILL_MODE fill_mode() const;

  /**
   * @brief Abstract method for drawing the figure.
   */
  virtual void draw(Canvas &cv, LINE_MODE mode = LINE_MODE::BRESENHAM) = 0;

  /**
   * @brief Fill the figure.
   */
  virtual void fill(Canvas &cv);

private:
  /* data */
  Color m_stroke_color, m_fill_color;
  int m_stroke_width;

  FILL_MODE m_fill_mode;
};

} // namespace rstzr

#endif
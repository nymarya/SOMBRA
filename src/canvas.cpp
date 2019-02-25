#include "canvas.h"

using component_t = unsigned char;
/**
 * @brief Constructor Default
 */
rast::Canvas::Canvas(const size_t width, const size_t height)
: m_width(width)
, m_height(height)
, m_fill_color (Color(0,0,0) )
, m_bkg_color (Color (255,255,255))
, m_pixels ( new component_t[(width*height*3)])
{ 
    
    for (unsigned int x = 0; x < m_width; x++)
  	{
  	    for (unsigned int y=0; y < m_height ; y++){
  		    m_pixels[                    m_width*y + x ] = m_bkg_color.red();
  		    m_pixels[ m_height*m_width + m_width*y + x ] = m_bkg_color.green();
  		    m_pixels[ m_height*m_width*2+ m_width*y + x ] = m_bkg_color.blue();
  		    
  	    }
  	}

}
            
/**
 * @brief Set the color of a pixel on the canvas
 */
//TODO: change x and y to Point2D
void rast::Canvas::pixel (const long x, const long y, const Color &c){
   // m_pixels[(x*m_width)+y] = c;
   m_pixels[ m_width*y + x] = c.red();
   m_pixels[m_height*m_width + m_width*y +x] = c.green();
   m_pixels[m_height*m_width*2+ m_width*y+ x] = c.blue();
}
 
/**
 * @brief Get the pixel color from canvas
 */
component_t rast::Canvas::pixel (const long x, const long y) const{
    return m_pixels[(x*m_width)+y];
}

/**
 * @brief Get the canvas width
 */
size_t 	rast::Canvas::width (void) const{
    return m_width;
}

/**
 * @brief Get the canvas height
 */
size_t 	rast::Canvas::height (void) const{
    return m_height;
}

/**
 * @brief Get the canvas pixels as an array of unsigned char.
 */
component_t* rast::Canvas::pixels (void) const{
    return m_pixels.get();
}
 
/**
 * @brief Draw a line between two points 2D
 * @see https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/
 */
void rast::Canvas::lineDDA (const long x0, const long y0, const long x1, const long y1){
    float dy = y1 - y0;
    float dx = x1 - x0;
    float y = y0;
    float x = x0;

    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float x_inc = dx / (float) steps; 
    float y_inc = dy / (float) steps; 

    for( int i = 0; i < steps; i++ ) {
      pixel(round(x),round(y), m_fill_color);
      y += y_inc;
      x += x_inc;
    }
}

/**
 * @brief Draw a line between two points 2D using the Bresenham algorithm.
 */
void rast::Canvas::lineBresenham(const long x0, const long y0, const long x1, const long y1){
    float dy = y1 - y0;
    float dx = x1 - x0;
    float p = 2 *dy - dx;
    float y = y0;
    float x = x0;

    pixel(x, y, m_fill_color);
    for( x = x0; x < x1; x++ ) {
      if( p < 0){
        p += 2 * dy;
      } else {
        y++;
        p += 2 * dy - 2 * dx;
      }
      pixel(x, y, m_fill_color);
    }
}


void rast::Canvas::bkg_color(const Color &c){
    m_bkg_color = c;
}

void rast::Canvas::fill_color(const Color &c){
    m_fill_color = c;
}
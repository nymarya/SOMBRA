#include "canvas.h"

using component_t = unsigned char;
/**
 * @brief Constructor Default
 */
rstzr::Canvas::Canvas(const size_t width, const size_t height)
: m_width(width)
, m_height(height)
, m_pixels ( new component_t[(width*height*3)])
, m_fill_color (Color(0,0,0) )
, m_bkg_color (Color (255,255,255))
{ 
    
    for (unsigned int x = 0; x < m_width; x++)
  	{
  	    for (unsigned int y=0; y < m_height ; y++){
          pixel(x, y, m_bkg_color);
  		    
  	    }
  	}

}
            
/**
 * @brief Set the color of a pixel on the canvas
 */
//TODO: change x and y to Point2D
void rstzr::Canvas::pixel (const long x, const long y, const Color &c){
   // m_pixels[(x*m_width)+y] = c;
   m_pixels[ m_width*y + x] = c.red();
   m_pixels[m_height*m_width + m_width*y +x] = c.green();
   m_pixels[m_height*m_width*2+ m_width*y+ x] = c.blue();
}
 
/**
 * @brief Get the pixel color from canvas
 */
component_t rstzr::Canvas::pixel (const long x, const long y) const{
    return m_pixels[(x*m_width)+y];
}

/**
 * @brief Get the canvas width
 */
size_t 	rstzr::Canvas::width (void) const{
    return m_width;
}

/**
 * @brief Get the canvas height
 */
size_t 	rstzr::Canvas::height (void) const{
    return m_height;
}

/**
 * @brief Get the canvas pixels as an array of unsigned char.
 */
component_t* rstzr::Canvas::pixels (void) const{
    return m_pixels.get();
}


/**
 * @brief Draw a line between two points 2D.
 */
void rstzr::Canvas::line(rstzr::Point2D &p1, rstzr::Point2D &p2, const Color &c, LINE_MODE mode){
    
    //Draw line based on choosen type
    if(mode == LINE_MODE::DDA)
      drawLineDDA(p1, p2, c);
    else if (mode == LINE_MODE::BRESENHAM)
      drawLineBresenham(p1, p2, c);
    else if(mode == LINE_MODE::COMPARE){
      drawLineDDA(p1,p2, Color(0,0,255));
      drawLineBresenham(p1, p2, Color(0, 255, 0));
    }
}


void rstzr::Canvas::bkg_color(const Color &c){
    m_bkg_color = c;
}

void rstzr::Canvas::fill_color(const Color &c){
    m_fill_color = c;
}

/**
 * @brief Get the color that will fill the object
 */
rstzr::Color rstzr::Canvas::fill_color() const{
  return m_fill_color;
}

/**
 * @brief Draw a line between two points 2D
 * @see https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/
 */
void rstzr::Canvas::drawLineDDA( rstzr::Point2D p1, rstzr::Point2D p2, const Color &c ){
    coord_type x0 = p1.x();
    coord_type x1 = p2.x();
    coord_type y0 = p1.y();
    coord_type y1 = p2.y();


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
      pixel(x,y, c);
      y += y_inc;
      x += x_inc;
    }
}

/**
 * @brief Draw a line between two points 2D using the brsenham algorithm
 * @see https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void rstzr::Canvas::drawLineBresenham( rstzr::Point2D p1, rstzr::Point2D p2, const Color &c){
    coord_type x0 = p1.x();
    coord_type x1 = p2.x();
    coord_type y0 = p1.y();
    coord_type y1 = p2.y();

    float dy = y1 - y0;
    float dx = x1 - x0;
    float p = 2 *dy - dx;
    float y = y0;
    float x = x0;

    // Align the points
    if ((x0 > x1) || (y0 > y1)){
      y0 = y1;
      y1 = y;

      x0 = x1;
      x1 = x;

      dy = y1 - y0;
      dx = x1-x0;
    }

    if (abs(dy) < abs(dx)){
      
        // plot low 
        for( x = x0; x < x1; x++ ) {
          pixel(x, y, c);
          if(p > 0) {
            y++;
            p += 2 * dy - 2 * dx;
          } else
            p += 2 * dy;
        }
    } else {
        // plot high
        auto xi = 1;
        if (dx < 0){
          xi = -1;
          dx = -dx;
        }
        p = 2*dx - dy ;

        for( y = y0; y < y1; y++ ) {
          pixel(x, y, c);

          if(p > 0) {
            x += xi;
            p -= 2 * dy;
          }
            
          p += 2 * dx;

        }
    }

    


}
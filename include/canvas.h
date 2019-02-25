#ifndef _canvas_h_
#define _canvas_h_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <math.h>

#include "color.h"

using component_t = unsigned char;


namespace rast{
    
    class Canvas {
        
        public:
        
            /**
             * @brief Constructor Default
             */
            Canvas(std::size_t width, std::size_t height);
    
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
             * @brief Get the canvas width
             */
            size_t 	width(void) const;

            /**
             * @brief Get the canvas height
             */
            size_t 	height(void) const;
            
            /**
             * @brief Get the canvas pixels as an array of unsigned char.
             */
            component_t* pixels (void) const;
 
            /**
             * @brief Draw a line between two points 2D
             */
            void lineDDA (const long x, const long y, const long x1, const long y1);

            /**
             * @brief Draw a line between two points 2D using the brsenham algorithm
             */
            void lineBresenham (const long x, const long y, const long x1, const long y1);
            
            void bkg_color(const Color &c);
            
            void fill_color(const Color &c);

        private:
            size_t 	m_width;
 
            size_t 	m_height;
             
            //n x m x 3
            std::unique_ptr< component_t[] > m_pixels;
            
            Color m_fill_color;
 
            Color m_bkg_color;
    };

    
}

#endif
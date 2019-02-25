#ifndef _color_h_
#define _color_h_

#include <iostream>

using color_t = unsigned char;

namespace rstzr{
    
    class Color{
        
        public:
            
            Color(color_t red , color_t green, color_t blue);
            
            ~Color() = default;

            Color& operator=( const Color& other );
            
            color_t red() const;
            
            color_t green() const;
            
            color_t blue() const;
            
            
        private:
            
            color_t * m_channels;
    };
}

#endif
#ifndef _color_h_
#define _color_h_

using color_t = unsigned char;

namespace rast{
    
    class Color{
        
        public:
            
            Color(color_t red =0 , color_t green=0, color_t blue=0);
            
            ~Color() = default;

            Color& operator=( const Color& other );
            
        private:
            
            color_t * m_channels;
    };
}

#include "color.inl"

#endif
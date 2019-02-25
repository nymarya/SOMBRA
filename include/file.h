#ifndef _file_h_
#define _file_h_

#include <string>
#include <fstream>
#include "canvas.h"

namespace rstzr{
    /**
     * Provide the method to read and save files
     */
    class File{
        
        public:
            
            File(std::string filename);
            
            ~File() = default;
            
            void read();
            
            void save_ppm( const rast::Canvas &canvas);
        
        private:
        
            std::string filename;
            
            // 0 -> read
            // 1 -> write
            int mode; 
    };
}


#endif
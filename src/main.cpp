
#include "../include/canvas.h"
#include "../include/file.h"

int main() 
{
     size_t width = 200;
     size_t height= 200;

     rast::Canvas c (width, height);

     c.lineDDA(10, 10, 30, 30);
     
     rstzr::File file ("teste");
     
     file.save_ppm(c);
     
     return 0;
}
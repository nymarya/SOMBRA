
#include "../include/canvas.h"
#include "../include/file.h"

int main() 
{
     size_t width = 200;
     size_t height= 200;



     ///////////////////////////
     /// increasing w/ error ///
     ///////////////////////////

     rast::Canvas c (width, height);

     c.lineDDA(199, 199, 10, 30);
     
     rstzr::File file ("increasing_dda_error");
     
     file.save_ppm(c);

     ///////////////////////////
     /// decreasing w/ error ///
     ///////////////////////////

     rast::Canvas c1 (width, height);

     c1.lineDDA(10, 10, 199, 100);
     
     rstzr::File file1 ("decreasing_dda_error");
     
     file1.save_ppm(c1);


     ///////////////////////////
     /// 45 degrees w/ error ///
     ///////////////////////////

     rast::Canvas c2 (width, height);

     c2.lineDDA(10, 10, 100, 100);
     
     rstzr::File file2 ("45_dda_error");
     
     file2.save_ppm(c2);

     ///////////////////////////
     /// horizontal w/ error ///
     ///////////////////////////

     rast::Canvas c3 (width, height);

     c3.lineDDA(10, 10, 10, 100);
     
     rstzr::File file3 ("hr_dda_error");
     
     file3.save_ppm(c3);

     ///////////////////////////
     ///  vertical w/ error ////
     ///////////////////////////
     rast::Canvas c4 (width, height);

     c4.lineDDA(10, 10, 199, 10);
     
     rstzr::File file4 ("vr_dda_error");
     
     file4.save_ppm(c4);

     
     return 0;
}
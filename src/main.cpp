
#include "../include/canvas.h"
#include "../include/file.h"

int main() 
{
     size_t width = 200;
     size_t height= 200;

     rstzr::Point2D p1 (10, 10);
     rstzr::Point2D p2 (199, 199);
     rstzr::Point2D p3 (10, 30);
     rstzr::Point2D p4 (199, 100);
     rstzr::Point2D p5 (100, 100);
     rstzr::Point2D p6 (10, 100);
     rstzr::Point2D p7 (199, 10);

     rstzr::Color fill_color (0,0,0);

     /**
      * DDA
      */

     ///////////////////////////
     /// increasing w/ error ///
     ///////////////////////////

     rstzr::Canvas c (width, height);

     c.lineDDA(p2, p3, fill_color);
     
     rstzr::File file ("increasing_dda_error");
     
     file.save_ppm(c);

     ///////////////////////////
     /// decreasing w/ error ///
     ///////////////////////////

     rstzr::Canvas c1 (width, height);

     c1.lineDDA(p1, p4, fill_color);
     
     rstzr::File file1 ("decreasing_dda_error");
     
     file1.save_ppm(c1);


     ///////////////////////////
     /// 45 degrees w/ error ///
     ///////////////////////////

     rstzr::Canvas c2 (width, height);

     c2.lineDDA(p1, p5, fill_color);
     
     rstzr::File file2 ("45_dda_error");
     
     file2.save_ppm(c2);

     ///////////////////////////
     /// horizontal w/ error ///
     ///////////////////////////

     rstzr::Canvas c3 (width, height);

     c3.lineDDA(p1, p6, fill_color);
     
     rstzr::File file3 ("hr_dda_error");
     
     file3.save_ppm(c3);

     ///////////////////////////
     ///  vertical w/ error ////
     ///////////////////////////
     rstzr::Canvas c4 (width, height);

     c4.lineDDA(p1, p7, fill_color);
     
     rstzr::File file4 ("vr_dda_error");
     
     file4.save_ppm(c4);

     /**
      * BRESENHAM
      */
     ///////////////////////////
     /// increasing w/ error ///
     ///////////////////////////

     rstzr::Canvas c5 (width, height);

     c5.lineDDA(p2, p3, fill_color);
     
     rstzr::File file5 ("increasing_bres_error");
     
     file5.save_ppm(c5);

     ///////////////////////////
     /// decreasing w/ error ///
     ///////////////////////////

     rstzr::Canvas c6 (width, height);

     c6.lineDDA(p1, p4, fill_color);
     
     rstzr::File file6 ("decreasing_bres_error");
     
     file6.save_ppm(c6);


     ///////////////////////////
     /// 45 degrees w/ error ///
     ///////////////////////////

     rstzr::Canvas c7 (width, height);

     c7.lineDDA(p1, p5, fill_color);
     
     rstzr::File file7 ("45_bres_error");
     
     file7.save_ppm(c7);

     ///////////////////////////
     /// horizontal w/ error ///
     ///////////////////////////

     rstzr::Canvas c8 (width, height);

     c8.lineDDA(p1, p6, fill_color);
     
     rstzr::File file8 ("hr_bres_error");
     
     file8.save_ppm(c8);

     ///////////////////////////
     ///  vertical w/ error ////
     ///////////////////////////
     rstzr::Canvas c9 (width, height);

     c9.lineDDA(p1, p7, fill_color);
     
     rstzr::File file9 ("vr_bres_error");
     
     file9.save_ppm(c9);

     
     return 0;
}
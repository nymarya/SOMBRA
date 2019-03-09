
#include "../include/canvas.h"
#include "../include/line.h"
#include "../include/file.h"

#include <vector>

using namespace rstzr;

int main()
{
     size_t width = 1000;
     size_t height = 1000;

     rstzr::Point2D p1(10, 10);
     rstzr::Point2D p2(10, 999);
     rstzr::Point2D p4(999, 500);
     rstzr::Point2D p5(500, 500);
     rstzr::Point2D p6(10, 500);
     rstzr::Point2D p7(999, 10);

     rstzr::Color fill_color(0, 0, 0);

     std::string dda = "_dda";
     std::string bresenham = "_bres";
     std::vector<std::string> filenames = {
         "increasing",
         "decreasing",
         "45",
         "hr",
         "vr",
     };

     std::vector<std::vector<rstzr::Point2D>> points = {
         {p2, p7},
         {p1, p4},
         {p1, p5},
         {p1, p6},
         {p1, p7}};
     /**
     // Run tests for DDA
     for (auto i = 0u; i < points.size(); i++)
     {
          rstzr::Canvas c(width, height);

          c.line(points[i][0], points[i][1], fill_color, LINE_MODE::DDA);

          rstzr::File file(filenames[i] + dda);

          file.save_ppm(c);
     }

     // Run tests for Bresenham's algorithm
     for (auto i = 0u; i < points.size(); i++)
     {
          rstzr::Canvas c(width, height);

          c.line(points[i][0], points[i][1], fill_color, LINE_MODE::BRESENHAM);

          rstzr::File file(filenames[i] + bresenham);

          file.save_ppm(c);
     }

     ///////////////////////////
     //// COMPARE           ////
     ///////////////////////////

     rstzr::Canvas c(width, height);

     c.line(p2, p7, fill_color, LINE_MODE::COMPARE);

     rstzr::File file("compare_dda_bres");

     file.save_ppm(c);

     ///////////////////////////
     //// COMPARE           ////
     ///////////////////////////

     rstzr::Point2D tl(1, 1);
     rstzr::Point2D tr(1, 999);
     rstzr::Point2D bl(999, 1);
     rstzr::Point2D br(999, 999);
     rstzr::Point2D m1(500, 1);
     rstzr::Point2D m2(1, 500);
     rstzr::Point2D m3(999, 500);
     rstzr::Point2D m4(500, 999);

     rstzr::Canvas c1(width, height);

     c1.line(tl, tr, fill_color, LINE_MODE::BRESENHAM);
     c1.line(tl, bl, fill_color, LINE_MODE::BRESENHAM);
     c1.line(tl, br, fill_color, LINE_MODE::BRESENHAM);
     c1.line(tr, bl, fill_color, LINE_MODE::BRESENHAM);
     c1.line(bl, br, fill_color, LINE_MODE::BRESENHAM);
     c1.line(tr, br, fill_color, LINE_MODE::BRESENHAM);
     c1.line(m1, m4, fill_color, LINE_MODE::BRESENHAM);
     c1.line(m2, m3, fill_color, LINE_MODE::BRESENHAM);

     rstzr::File file1("bres");

     file1.save_ppm(c1);

     /////////////////////////
     //////// CIRCLE  ////////
     ////////////////////////
     rstzr::Canvas c2(width, height);
     rstzr::Circle circle(50, Point2D(100, 100));
     c2.circle(circle, fill_color);
     rstzr::File file2("circle");

     file2.save_ppm(c2);

     rstzr::Canvas c3(width, height);
     rstzr::Circle circle1(60, Point2D(60, 100));
     c3.circle(circle1, fill_color);
     rstzr::File file3("circle2");

     file3.save_ppm(c3);

     ///////////////////////////
     //// ANTIALISING       ////
     ///////////////////////////

     Canvas c4(width, height);

     rstzr::Circle circle(200, Point2D(500, 500));
     c4.circle(circle, fill_color);

     //c4.antiliasing();

     File file4("bres_circle");

     file4.save_ppm(c4);
     **/

     return 0;
}
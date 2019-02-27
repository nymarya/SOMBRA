
#include "../include/canvas.h"
#include "../include/line.h"
#include "../include/file.h"

#include <vector>

int main()
{
     size_t width = 200;
     size_t height = 200;

     rstzr::Point2D p1(10, 10);
     rstzr::Point2D p2(10, 199);
     rstzr::Point2D p4(199, 100);
     rstzr::Point2D p5(100, 100);
     rstzr::Point2D p6(10, 100);
     rstzr::Point2D p7(199, 10);

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

     // Run tests for DDA
     for (int i = 0; i < points.size(); i++)
     {
          rstzr::Canvas c(width, height);

          c.line(points[i][0], points[i][1], fill_color, LINE_MODE::DDA);

          rstzr::File file(filenames[i] + dda);

          file.save_ppm(c);
     }

     // Run tests for Bresenham's algorithm
     for (int i = 0; i < points.size(); i++)
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
     rstzr::Point2D tr(1, 199);
     rstzr::Point2D bl(199, 1);
     rstzr::Point2D br(199, 199);
     rstzr::Point2D m1(100, 1);
     rstzr::Point2D m2(1, 100);
     rstzr::Point2D m3(199, 100);
     rstzr::Point2D m4(100, 199);

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

     return 0;
}
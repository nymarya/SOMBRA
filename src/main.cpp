
#include "../include/canvas.h"
#include "../include/line.h"
#include "../include/file.h"
#include "../include/graphic.h"
#include "../include/arc.h"

#include <vector>
#include <map>
#include <iomanip> // std::setw

using namespace rstzr;

int main()
{
     /**
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

     // Run tests for DDA
     for (auto i = 0u; i < points.size(); i++)
     {
          rstzr::Canvas c(width, height);

          Line line(points[i][0], points[i][1], fill_color);

          c.draw(line, LINE_MODE::DDA);

          rstzr::File file(filenames[i] + dda);

          file.save_ppm(c);
     }

     // Run tests for Bresenham's algorithm
     for (auto i = 0u; i < points.size(); i++)
     {
          rstzr::Canvas c(width, height);
          Line line(points[i][0], points[i][1], fill_color);

          c.draw(line, LINE_MODE::BRESENHAM);

          rstzr::File file(filenames[i] + bresenham);

          file.save_ppm(c);
     }

     ///////////////////////////
     //// COMPARE           ////
     ///////////////////////////

     rstzr::Canvas c(width, height);

     Line line(p2, p7, fill_color);

     c.draw(line, LINE_MODE::COMPARE);

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

     Line line1(tl, tr, fill_color);
     Line line2(tl, bl, fill_color);
     Line line3(tl, br, fill_color);
     Line line4(tr, bl, fill_color);
     Line line5(bl, br, fill_color);
     Line line6(tr, br, fill_color);
     Line line7(m1, m4, fill_color);
     Line line8(m2, m3, fill_color);

     c1.draw(line1, LINE_MODE::BRESENHAM);
     c1.draw(line2, LINE_MODE::BRESENHAM);
     c1.draw(line3, LINE_MODE::BRESENHAM);
     c1.draw(line4, LINE_MODE::BRESENHAM);
     c1.draw(line5, LINE_MODE::BRESENHAM);
     c1.draw(line6, LINE_MODE::BRESENHAM);
     c1.draw(line7, LINE_MODE::BRESENHAM);
     c1.draw(line8, LINE_MODE::BRESENHAM);

     rstzr::File file1("bres");

     file1.save_ppm(c1);

     /////////////////////////
     //////// CIRCLE  ////////
     ////////////////////////
     rstzr::Canvas c2(width, height);
     rstzr::Circle circle(50, Point2D(100, 100), fill_color);
     c2.draw(circle);
     rstzr::File file2("circle");

     file2.save_ppm(c2);

     rstzr::Canvas c3(width, height);
     rstzr::Circle circle1(60, Point2D(60, 100), fill_color);
     c3.draw(circle1);
     rstzr::File file3("circle2");

     file3.save_ppm(c3);

     ///////////////////////////
     //// ANTIALISING       ////
     ///////////////////////////

     Canvas c4(width, height);

     rstzr::Circle circle2(200, Point2D(500, 500), fill_color);
     c4.draw(circle2);

     //c4.antiliasing();

     File file4("bres_circle");

     file4.save_ppm(c4);

     ///////////////////////////
     //// ARC       ////
     ///////////////////////////

     Canvas c5(width, height);

     rstzr::Arc arc(Point2D(500, 500), 135, 45, 100, fill_color);
     c5.draw(arc);

     //c4.antiliasing();
     

     File file5("arc");

     file5.save_ppm(c5);**/
     /**
     Canvas c6(width, height);

     rstzr::Arc arc1(Point2D(500, 500), 0, 360, 100, fill_color);
     c6.draw(arc1);

     //c4.antiliasing();

     File file6("arc_circle");

     file6.save_ppm(c6);**/

     // Get argument with name of file containing the scene

     // Create canvas
     Canvas canvas(100, 100);

     // Read file
     File file("windows.json");
     std::vector<std::unique_ptr<Graphic>> objects = file.read(canvas);

     // Draw objects
     std::vector<std::unique_ptr<Graphic>>::iterator it = objects.begin();
     while (it != objects.end())
     {
          it->get()->draw(canvas);
          it++;
     }

     canvas.boundary_fill(Point2D(50, 100), Color(255,83,13), Color(0,0,0));

     canvas.antiliasing();

     // Save final image
     file.save_ppm(canvas);

     return 0;
}
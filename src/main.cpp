
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
          it->get()->fill(canvas);
          it++;
     }

     //canvas.boundary_fill(Point2D(50, 100), Color(255,83,13), Color(0,0,0));

     //canvas.antiliasing();

     // Save final image
     file.save_ppm(canvas);

     return 0;
}
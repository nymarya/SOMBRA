#ifndef _line_h_
#define _line_h_

#include <vector>

#include "color.h"
#include "point.h"

namespace rstzr{

	class Canvas;

	/**
	 * @brief Class that represents a line
	 */
	class Line
	{
		public:
			/**
			 * @brief Constructor for class Line.
			 */
			Line(Point2D p1, Point2D p2);

			/**
			 * @brief Destructor 
			 */
			~Line() = default;

			/**
             * @brief Draw a line between two points 2D
             */
			void drawDDA(  Canvas &cv, const Color &c );

			/**
             * @brief Draw a line between two points 2D using the brsenham algorithm
             */
			void drawBresenham ( Canvas &cv,  const Color &c);

			/**
			 * @brief Draw a line in a canvas.
			 */
			void draw(Canvas &cv,  const Color &c, LINE_MODE mode);
		
		private:

			Point2D m_p1;
			Point2D m_p2;

			coord_type y_max;
			coord_type x_min;
			float slope; //dx/dy	
	};
}

#endif
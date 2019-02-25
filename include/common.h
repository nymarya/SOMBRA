#ifndef _common_h_
#define _common_h_

using component_t = unsigned char;

typedef long coord_type;

enum LINE_MODE{
	DDA ,
	BRESENHAM,
	COMPARE
};

#endif
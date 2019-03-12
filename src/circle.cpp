#include "../include/circle.h"

/**
 * @brief Create circle based on json file
 */
rstzr::Circle::Circle(json &j)
    : Arc(j, 0, 360)
{
}

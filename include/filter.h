#ifndef _filter_h_
#define _filter_h_

#include "common.h"
#include "point.h"
#include <iostream>
#include <vector>
#include <map>
namespace rstzr
{

void multiply(component_t matrix[], size_t size, const component_t mask[], size_t size2);

void canny(component_t matrix[], size_t size);
} // namespace rstzr

#endif
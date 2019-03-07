#ifndef _filter_h_
#define _filter_h_

#include "common.h"
#include "point.h"
#include <iostream>
#include <vector>
#include <map>
#include <math.h>

namespace rstzr
{

void gray(component_t matrix[], component_t pic[], size_t width, size_t height);

std::vector<int> canny(component_t matrix[], size_t, size_t);

void magnitude_matrix(component_t pic[], component_t *mag, double *x, double *y, component_t width, component_t height);

std::vector<Point2D *> peak_detection(component_t *mag, std::map<int, int> &h, double *x, double *y,
                                      component_t width, component_t height);

void recursiveDT(component_t mag[], component_t *final, std::map<int, int> &h, std::map<int, int> &peaks,
                 int a, int b, int flag, size_t height, size_t width, std::vector<int> &result);

} // namespace rstzr

#endif
#ifndef SPLINE_H
#define SPLINE_H

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <QString>
#include "rtm.h"

extern std::vector<std::pair<double, double>> XY;
extern int n;

std::vector<double> find_h();
std::vector<double> spline(std::vector<double>& hi);
std::vector<double> S(int i, std::vector<double>& m, std::vector<double>& hi);
QString getStringPolinome(std::vector<double>& polinome);

#endif // SPLINE_H

#pragma once
#include <vector>
#include "matrix.h"

double Pi(double ai, double bi, double ci, double P);
double Qi(double ai, double bi, double di, double P, double Q);
std::vector<double> rtm(const Matrix& M);

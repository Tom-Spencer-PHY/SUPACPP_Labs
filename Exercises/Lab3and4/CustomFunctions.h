#pragma once

#include <cmath>

double normal(double x, double mean, double stdDev);
double cauchyLorentz(double x, double gamma, double x_0);
double crystalBall(double x, double mean, double stdDev, double n, double alpha);
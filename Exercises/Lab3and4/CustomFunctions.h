#include <cmath>

#pragma once

double normal(double x, double norm_mean, double norm_sigma);
double cauchyLorentz(double x, double cauchy_mean, double gamma);
double crystalBall(double x, double cb_mean, double cb_sigma, double cb_n, double cb_alpha);
#include "CustomFunctions.h"
#include <iostream>

// Define the custom functions used to test the data
double normal(double x, double mean, double stdDev){
    double a = 1/(stdDev * sqrt(M_PI*2));
    double z = (x - mean) / stdDev;
    return a * pow(M_E, - 0.5 * pow(z, 2));
}

double cauchyLorentz(double x, double x_0, double gamma){
    return 1 /( M_PI * gamma * (1 + pow((x - x_0)/ gamma, 2)));
}

double crystalBall(double x, double mean, double stdDev, double n, double alpha){
    double A = pow((n / abs(alpha)), n) * pow(M_E, - 1/2 * pow(abs(alpha),2));
    double B = n/abs(alpha) - abs(alpha);
    double C = n/abs(alpha) * 1/(n-1) * pow(M_E, - 1/2 * pow(abs(alpha),2));
    double D = sqrt(M_PI_2) * (1 + erf(abs(alpha) / sqrt(2)));
    double N = 1 / (stdDev * (C + D));
    double upper = N * pow(M_E, - pow(abs(x - mean),2) / (2 * pow(stdDev, 2)));
    double lower = N * A * pow(B - (x - mean)/stdDev, -n);

    if ((x - mean)/stdDev > - alpha) return upper;
    else return lower;
}
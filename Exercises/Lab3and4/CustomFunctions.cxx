#include "CustomFunctions.h"
#include <iostream>

// Define the custom functions used to test the data
double normal(double x, double norm_mean, double norm_sigma){
    double a = 1/(norm_sigma * sqrt(M_PI*2));
    double z = (x - norm_mean) / norm_sigma;
    return a * exp(- 0.5 * pow(z, 2));
}

double cauchyLorentz(double x, double x_0, double gamma){
    return 1 /( M_PI * gamma * (1 + pow((x - x_0)/ gamma, 2)));
}

double crystalBall(double x, double cb_mean, double cb_sigma, double cb_n, double cb_alpha){
    double absAlpha = abs(cb_alpha);
    double t = (x - cb_mean) / cb_sigma;
    
    double A = pow((cb_n / absAlpha), cb_n) * exp(- 0.5 * absAlpha * absAlpha);
    double B = cb_n/absAlpha - absAlpha;
    double C = cb_n/absAlpha * 1/(cb_n-1) * exp(- 0.5 * absAlpha * absAlpha);
    double D = sqrt(M_PI_2) * (1 + erf(absAlpha / sqrt(2.0)));
    double N = 1 / (cb_sigma * (C + D));
    double upper = N * exp(-0.5 * t * t);
    double lower = N * A * pow(B - t, -cb_n);

    if (t > - absAlpha) {
        return N * exp(-0.5 * t * t);
    } else {
        return N * A * pow(B - t, -cb_n);
    }
}
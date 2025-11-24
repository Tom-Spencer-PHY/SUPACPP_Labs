#include "customFunctions.hh"

#include <iostream>
#include <fstream>
#include <vector>

// g++ -std=c++23 analyseData.cpp $(root-config --libs) -o analyseData

int main(int argc, char** argv) {
    // Get vector of x,y points from file
    std::vector<std::vector<float>> xy_points = readData("input2D_float.txt");
    std::vector<std::vector<float>> xy_errors = readData("error2D_float.txt");

    // Give user choice to display specified number of lines
    printUserLines(xy_points);

    // Get vectors of point magnitudes, least squares fit, and exponentials, plus chi-squared values
    std::vector<float> magnitudes = pointMagnitude(xy_points);
    std::vector<float> least_squares_parameters = calcLeastSqaures(xy_points);
    std::vector<float> exponentials = xToTheY(xy_points);
    float chi_squared = calcChiSquared(xy_points, xy_errors, least_squares_parameters);
    float chi_squared_NDOF = chi_squared/(xy_points.size() - 2); //linear fit has (N data points - 2 parameters) DOF

    // Display and/or write magnitudes
    int disp_mags = getUserInt("Enter 0 to skip, 1 to display only, 2 to save only, and 3 for both for magnitudes: ", 3, 0);
    if (disp_mags == 1 or disp_mags == 3) printUserLines(magnitudes, "magnitudes");
    if (disp_mags == 2 or disp_mags == 3) saveOutput(magnitudes, "magnitudes.txt");
    
    // Display and/or write chi squared
    int disp_chi = getUserInt("Enter 0 to skip, 1 to display only, 2 to save only, and 3 for both for chi-squared: ", 3, 0);
    if (disp_chi == 1 or disp_chi == 3) printUserLines(least_squares_parameters, chi_squared, chi_squared_NDOF);
    if (disp_chi == 2 or disp_chi == 3) saveOutput(least_squares_parameters, chi_squared, chi_squared_NDOF);

    
    // Display and/or write exponentials, x^(rounded y)
    int disp_exps = getUserInt("Enter 0 to skip, 1 to display only, 2 to save only, and 3 for both for exponentials: ", 3, 0);
    if (disp_exps == 1 or disp_exps == 3) printUserLines(exponentials, "exponentials");
    if (disp_exps == 2 or disp_exps == 3) saveOutput(exponentials, "exponentials.txt");
    
    return 0;
}
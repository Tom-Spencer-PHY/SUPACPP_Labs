#pragma once

#include <string>
#include <vector>

//Defining prototype functions, implementation in customFunctions.cpp

// User input
int getUserInt(const std::string& prompt, int maxValue, int default_value);

// Reading data
std::vector<std::vector<float>> readData(std::string input_data_name);

// Printing data
void printUserLines(const std::vector<float>& x_points, const std::string& returnType);
void printUserLines(const std::vector<float>& least_sqaures_parameters, const float& chi_squared, const float& chi_squared_NDOF);
void printUserLines(const std::vector<std::vector<float>>& xy_points);

// Writing data
void saveOutput(const std::vector<float>& x_points, const std::string& filename);
void saveOutput(const std::vector<float>& least_sqaures_parameters, const float& chi_squared, const float& chi_squared_NDOF);

// Maths
std::vector<float> pointMagnitude(const std::vector<std::vector<float>>& xy_points);

std::vector<float> calcLeastSqaures(const std::vector<std::vector<float>>& xy_points);

float calcChiSquared(const std::vector<std::vector<float>>& xy_points, 
                     const std::vector<std::vector<float>>& xy_errors,
                     const std::vector<float>& least_squares_parameters);

float personalPower(float x, int rounded_y);

std::vector<float> xToTheY(std::vector<std::vector<float>> xy_points);

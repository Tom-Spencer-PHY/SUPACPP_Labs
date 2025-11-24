#include "customFunctions.hh"

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>


// User input
int getUserInt(const std::string& prompt, int maxValue, int default_value) {
    int value = 0;
    std::cout << prompt;
    std::cin >> value;
    if (value < 0 or value > maxValue) {
        std::cout << "Invalid input, using default: " << default_value << std::endl;
        value = default_value;
    }
    return value;
}

// Reading data
std::vector<std::vector<float>> readData(std::string input_data_name) {
    std::ifstream input(input_data_name);
    if (!input.is_open()) {
        std::cerr << "Error: Could not open file '" << input_data_name << "'!" << std::endl;
        return {};
    }
    
    std::string line;
    std::vector<std::vector<float>> xy_points;

    // Read every line from the file
    for (int i = 0; std::getline(input, line); i++){
        std::stringstream ss(line);
        std::vector<float> point;
        std::string vector_component;
        if(i == 0) continue; //skip the first (x,y) line
        while (std::getline(ss, vector_component, ',')) {
            point.push_back(std::stof(vector_component));
        }
        xy_points.push_back(point);
    }
    return xy_points;
}


// Printing data. Vector of x, or (x,y) - overloaded
void printUserLines(const std::vector<float>& x_points, const std::string& returnType){
    int line_count = x_points.size();
    std::string prompt = "Enter number of data lines to display, maximum " + std::to_string(line_count) + ": ";
    int user_num_lines = getUserInt(prompt, line_count, 5);
    std::cout << "Printing " << user_num_lines << " lines of data" << std::endl;
    for (int line_num = 0; line_num < user_num_lines; ++line_num){
        if (returnType == "magnitudes") {
            std::cout << line_num+1 << " magntude = " << x_points[line_num] << std::endl;
        } else if (returnType == "exponentials") {
            std::cout << line_num+1 << " x^y = " << x_points[line_num] << std::endl;
        }
    }
}
void printUserLines(const std::vector<float>& least_squares_parameters, const float& chi_squared, const float& chi_squared_NDOF){
    std::cout << "y = " << least_squares_parameters[0] << "x + " << least_squares_parameters[1] << std::endl;
    std::cout << "Chi-squared value: " << chi_squared << ", chi-squared/NDOF value: " << chi_squared_NDOF << std::endl;
}
void printUserLines(const std::vector<std::vector<float>>& xy_points){
    int line_count = xy_points.size();
    std::string prompt = "Enter number of data lines to display, maximum " + std::to_string(line_count) + ": ";
    int user_num_lines = getUserInt(prompt, line_count, 5);
    std::cout << "Printing " << user_num_lines << " lines of data" << std::endl;
    for (int line_num = 0; line_num < user_num_lines; ++line_num){
        std::vector<float> data_point = xy_points[line_num];
        std::cout << "x = " << data_point[0] << ", y = " << data_point[1] << std::endl;
    }
}

// Saving data. Vector of x, or (x,y) - overloaded
void saveOutput(const std::vector<float>& x_points, const std::string& filename){
    std::ofstream outfile("Outputs/" + filename);
    if (!outfile.is_open()) {
            std::cerr << "Error: Could not open file Outputs/" << filename << std::endl;
    } else {
        int line_count = x_points.size();
        std::string prompt = "Enter number of data lines to save, maximum " + std::to_string(line_count) + ": ";
        // int getUserInt(const std::string& prompt, int maxValue, int default_value)
        int user_num_lines = getUserInt(prompt, line_count, 5);
        std::cout << "Saving " << user_num_lines << " lines of data" << std::endl;
        for (int line_num = 0; line_num < user_num_lines; ++line_num){
            outfile << x_points[line_num] << std::endl;
        }
        outfile.close();
    }
}
void saveOutput(const std::vector<float>& least_squares_parameters, const float& chi_squared, const float& chi_squared_NDOF){
    std::ofstream outfile("Outputs/chi_squared.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file for writing chi-squared output!" << std::endl;
    } else {
        outfile << "y = " << least_squares_parameters[0] << "x + " << least_squares_parameters[1] << std::endl;
        outfile << "Chi-squared value: " << chi_squared << ", chi-squared/NDOF value: " << chi_squared_NDOF << std::endl;
        outfile.close();
    }
}


// Maths
// Magnitude of points
std::vector<float> pointMagnitude(const std::vector<std::vector<float>>& xy_points){
    std::vector<float> magnitudes;
    for (const auto& point : xy_points) {
        float x = point[0];
        float y = point[1];
        float magnitude = std::sqrt(x*x + y*y);
        magnitudes.push_back(magnitude);
    }
    return magnitudes;
}

// Least squares
std::vector<float> calcLeastSqaures(const std::vector<std::vector<float>>& xy_points){
    std::vector<float> least_squares_parameters; // y = p*x + q, stored as [p,q]
    float sum_x = 0.0, sum_y = 0.0, sum_xx = 0.0, sum_yy = 0.0, sum_xy = 0.0;
    int n = xy_points.size();
    for (const auto& point : xy_points) {
        sum_x += point[0];
        sum_y += point[1];
        sum_xx += point[0]*point[0];
        sum_yy += point[1]*point[1];
        sum_xy += point[0]*point[1];
    }
    //std::cout << "sumx: " << sum_x << ", sumy: " << sum_y << ", sumxx: " << sum_xx << ", sumyy: " << sum_yy << ", sumxy: " << sum_xy << std::endl;
    least_squares_parameters.push_back( (n*sum_xy - sum_x*sum_y)/(n*sum_xx-sum_x*sum_x) );
    least_squares_parameters.push_back( (sum_xx*sum_y - sum_xy*sum_x)/(n*sum_xx-sum_x*sum_x) );
    return least_squares_parameters;
}

// Chi squared
float calcChiSquared(const std::vector<std::vector<float>>& xy_points, 
                     const std::vector<std::vector<float>>& xy_errors,
                     const std::vector<float>& least_squares_parameters) {
    float chi_value = 0.0; //chi_squared = sum{(observed-expected)^2/variance}
    // y = p*x + q
    float p = least_squares_parameters[0]; 
    float q = least_squares_parameters[1];
    float expected = 0.0, eff_var = 0.0, diff = 0.0;

    for (size_t point_num = 0; point_num < xy_points.size(); ++point_num) {
        const auto& point = xy_points[point_num];
        const auto& point_err = xy_errors[point_num];
        eff_var = point_err[0]*point_err[0]*p*p + point_err[1]*point_err[1];
        expected = p*point[0] + q;
        diff = point[1] - expected;
        chi_value += diff*diff/eff_var;
    }
    return chi_value;
}

// Recursive exponentiation function
float personalPower(float x, int rounded_y) {
    if (rounded_y == 0) return 1.0;
    else if (rounded_y == 1) return x;
    else if (rounded_y < 0) return 1.0 / personalPower(x, -rounded_y);
    else return x * personalPower(x, rounded_y -1);
}

// Vector exponetiation
std::vector<float> xToTheY(std::vector<std::vector<float>> xy_points){
    std::vector<float> x_to_the_y;
    for (const auto& point : xy_points) {
        float x = point[0];
        int rounded_y = std::round(point[1]);
        float x_to_y = personalPower(x, rounded_y);
        x_to_the_y.push_back(x_to_y);
    }
    return x_to_the_y;
}
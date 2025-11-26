#include "FiniteFunctions.h"
#include "TestFiniteFunctions.h"
#include "CustomFunctions.h"

#include <iostream>

// Reading data
std::vector<double> readData(const std::string &input_data_name) {
    std::string filepath = "Outputs/data/" + input_data_name;
    std::ifstream input(filepath);
    if (!input.is_open()) {
        std::cerr << "Error: Could not open file '" << input_data_name << "'!" << std::endl;
        return {};
    }
    
    std::string line;
    std::vector<double> data_points;

    // Read every line from the file
    while (std::getline(input, line)){
        if (line.empty()) continue;
        data_points.push_back(std::stod(line));
    }
    return data_points;
}


int main() {
    std::vector<double> data_points = readData("MysteryData15330.txt");
    double norm_mean = 0.0, norm_sigma = 1.0;
    FiniteFunction fnormal(-10.0, 10.0, "normal.png", [norm_mean,norm_sigma](double x){return normal(x, norm_mean, norm_sigma);});
    fnormal.plotFunction();
    fnormal.printInfo();
    fnormal.plotData(data_points, 100);

    double x0 = 0.0, gamma = 1.0;
    FiniteFunction fcauchLorentz(-10.0, 10.0, "cauchLorentz.png", [x0,gamma](double x){return cauchyLorentz(x, x0, gamma);});
    fcauchLorentz.plotFunction();
    fcauchLorentz.printInfo();
    fcauchLorentz.plotData(data_points, 100);

    double cb_mean=0.0, cb_sigma=1.0, n=2.0, alpha=1.5;
    FiniteFunction fcrystalBall(-10.0, 10.0, "crystalBall.png", [alpha,n,cb_mean,cb_sigma](double x){ return crystalBall(x, alpha, n, cb_mean, cb_sigma); });
    fcrystalBall.plotFunction();
    fcrystalBall.printInfo();
    fcrystalBall.plotData(data_points, 100);
    return 0;
}
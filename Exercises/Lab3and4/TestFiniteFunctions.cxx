#include "FiniteFunctions.h"
#include "TestFiniteFunctions.h"
#include "CustomFunctions.h"
#include "infoHandler.h"

#include <iostream>
#include <random>

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

// Saving data
void saveOutput(const std::vector<double>& x_points, const std::string& filename){
    std::ofstream outfile("Outputs/data/" + filename);
    if (!outfile.is_open()) {
            std::cerr << "Error: Could not open file Outputs/" << filename << std::endl;
    } else {
        int line_count = x_points.size();
        std::cout << "Saving " << line_count << " lines of data" << std::endl;
        for (int line_num = 0; line_num < line_count; ++line_num){
            outfile << x_points[line_num] << std::endl;
        }
        outfile.close();
    }
}


double genRandNum(const double &min, const double &max) {
    std::random_device randGen;
    std::mt19937 gen(randGen()); // Mersenne Twister, random 32-bit number
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

double genRandNormNum(const double &mean, const double &sigma) {
    std::random_device randGen;
    static thread_local std::mt19937 gen(randGen()); // Mersenne Twister, random 32-bit number
    std::normal_distribution<double> dist(mean, sigma);
    return dist(gen);
}

void doRecursiveMetropolis(const std::function<double(double)> &func, std::vector<double> &results, double xi, double rMin, double rMax, int nSamples){
    if (int(results.size()) >= nSamples) return;
    double y = genRandNormNum(xi, 3.0);
    int tries = 0;
    const int maxTries = 100000;
    while ((y < rMin || y > rMax) && ++tries < maxTries){
        y = genRandNormNum(xi, 3.0);
        //std::cout << "Try number " << tries << " for y = " << y << std::endl;
    } if (tries >= maxTries) {
        doRecursiveMetropolis(func, results, xi, rMin, rMax, nSamples);
    }
    //std::cout << "Succeeded on try number " << tries << std::endl;

    double A = std::min(1.0, func(y)/func(xi));
    double T = genRandNum(0.0,1.0);
    //std::cout << "trying y = " << y << " and xi = " << xi << std::endl;
    //std::cout << "For T = " << T << " and A = " << A << std::endl;
    if (T<A) {
        results.push_back(y);
        std::cout << "Added " << results.back() << ", length now " << int(results.size()) << std::endl;
        doRecursiveMetropolis(func, results, y, rMin, rMax, nSamples);
    } else {
        std::cout << "failed, going again with " << int(results.size()) << " entries so far" << std::endl;
        doRecursiveMetropolis(func, results, xi, rMin, rMax, nSamples);
    }
}

std::vector<double> recursiveMetropolis(const std::function<double(double)> &func, double xi, double rMin, double rMax, int nSamples) {
    std::vector<double> results;
    results.reserve(nSamples);
    doRecursiveMetropolis(func, results, xi, rMin, rMax, nSamples);
    return results;
}

std::vector<double> genRandNums(const int &numRand, const double &min, const double &max) {
    std::vector<double> randNums;
    std::random_device randGen;
    std::mt19937 gen(randGen()); // Mersenne Twister, random 32-bit number
    std::uniform_real_distribution<double> dist(min, max);
    for (int i = 0; i < numRand; i++){
        randNums.push_back(dist(gen));
    }
    return randNums;
}

int main(int argc, char *argv[]) {

    // Finding the mystery function
    std::vector<std::string> inputs(argv + 1, argv+argc); // Ignore executable call
    // Input format is function type - mandatory, function parameters (mean, sigma/gamma, n, alpha) - optional
    
    std::string funct_name = "";
    if (!inputs.empty()){
        funct_name = inputs[0];
    }; // Options are norm, cauchy, cb
    int n_points = 100;
    double rMin = -10.0, rMax = 10.0;
    double norm_mean = 2.0, norm_sigma = 1.0;
    double cauchy_mean = 2.0, gamma = 2.0; // Correct parameters
    double cb_mean = 2.0, cb_sigma = 1.0, cb_n = 2.0, cb_alpha = 1.5;

    if (funct_name == "norm"){
        if (inputs.size() >= 2 ){
            norm_mean = std::stod(inputs[1]);
        } if (inputs.size() >= 3 ){
            norm_sigma = std::stod(inputs[2]);
        } if (inputs.size() >= 4 ){
            std::cout << "Too many inputs, ignoring everything beyond " << norm_sigma << std::endl;
        }
    }
    if (funct_name == "cauchy"){
        if (inputs.size() >= 2 ){
            cauchy_mean = std::stod(inputs[1]);
        } if (inputs.size() >= 3 ){
            gamma = std::stod(inputs[2]);
        } if (inputs.size() >= 4 ){
            std::cout << "Too many inputs, ignoring everything beyond " << gamma << std::endl;
        }
    }
    if (funct_name == "cb"){
        if (inputs.size() >= 2 ){
            cb_mean = std::stod(inputs[1]);
        } if (inputs.size() >= 3 ){
            cb_sigma = std::stod(inputs[2]);
        } if (inputs.size() >= 4 ){
            cb_n = std::stod(inputs[3]);
        } if (inputs.size() >= 5 ){
            cb_alpha = std::stod(inputs[4]);
        } if (inputs.size() >= 6 ){
            std::cout << "Too many inputs, ignoring everything beyond " << cb_alpha << std::endl;
        }
    }

    std::string output_name = ("Outputs/png/" + funct_name + ".png").c_str();

    infoHandler info("info");
    info.print(INFO, "Function name: " + funct_name);

    info.print(VERBOSE, "norm_mean: " + std::to_string(norm_mean));
    info.print(VERBOSE, "norm_sigma: " + std::to_string(norm_sigma));

    info.print(VERBOSE, "cauchy_mean: " + std::to_string(cauchy_mean));
    info.print(VERBOSE, "gamma: " + std::to_string(gamma));

    info.print(VERBOSE, "cb_mean: " + std::to_string(cb_mean));
    info.print(VERBOSE, "cb_sigma: " + std::to_string(cb_sigma));
    info.print(VERBOSE, "cb_n: " + std::to_string(cb_n));
    info.print(VERBOSE, "cb_alpha " + std::to_string(cb_alpha));



    std::vector<double> data_points = readData("MysteryData15330.txt");

    if (funct_name == "norm"){
        FiniteFunction fNormal(rMin, rMax, "normal.png", [norm_mean,norm_sigma](double x){return normal(x, norm_mean, norm_sigma);});
        fNormal.plotFunction();
        fNormal.printInfo();
        fNormal.plotData(data_points, n_points);
    }

    if (funct_name == "cauchy" || funct_name == ""){
        FiniteFunction fCauchyLorentz(rMin, rMax, "cauchyLorentz.png", [cauchy_mean,gamma](double x){return cauchyLorentz(x, cauchy_mean, gamma);});
        fCauchyLorentz.plotFunction();
        fCauchyLorentz.printInfo();
        fCauchyLorentz.plotData(data_points, n_points);
    }

    if (funct_name == "cb"){
        FiniteFunction fCrystalBall(rMin, rMax, "crystalBall.png", [cb_mean,cb_sigma,cb_n,cb_alpha](double x){return crystalBall(x, cb_mean, cb_sigma, cb_n, cb_alpha);});
        fCrystalBall.plotFunction();
        fCrystalBall.printInfo();
        fCrystalBall.plotData(data_points, n_points);
    }

    // Sampling
    auto normalFunc = [&](double xx) {return normal(xx, norm_mean, norm_sigma);};
    auto cauchyFunc = [&](double xx) {return cauchyLorentz(xx, cauchy_mean, gamma);};
    auto crystalFunc = [&](double xx) {return crystalBall(xx, cb_mean, cb_sigma, cb_n, cb_alpha);};


    // Replace CauchyFunc to sample from a different distribution
    std::vector<double> result = recursiveMetropolis(cauchyFunc, genRandNum(rMin, rMax), rMin, rMax, 30000);
    std::cout << "ran the function" << std::endl;

    saveOutput(result, "sampleData.txt");
    
    std::vector<double> data_sample = readData("sampleData.txt");
    
    FiniteFunction fSampleData(rMin, rMax, "sampledFit.png", [cauchy_mean,gamma](double x){return cauchyLorentz(x, cauchy_mean, gamma);});
    fSampleData.setFunctionName("Cauchy-Lorentz, x_{0} = 2, γ=2");
    fSampleData.plotFunction();
    fSampleData.printInfo();
    fSampleData.plotData(result, n_points);

    return 0;
}
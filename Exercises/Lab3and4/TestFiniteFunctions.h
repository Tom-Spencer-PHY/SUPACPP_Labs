#include <string>
#include <vector>
#include <functional>

#pragma once

// Reading data
std::vector<double> readData(const std::string &input_data_name);

// Saving sample data
void saveOutput(const std::vector<double>& x_points, const std::string& filename);

// Sampling the function
double genRandNum(const double &min, const double &max);
double genRandNormNum(const double &mean, const double &sigma);
std::vector<double> genRandNums(const int &numRand, const double &min, const double &max);

// Metropolis-style sampler (free function used by tests)
// func: target (unnormalised) density function
// x0: ignored (initial xi is chosen uniformly in [rMin,rMax])
// sig: proposal standard deviation
// rMin/rMax: domain limits (proposals outside are rejected)
// nSamples: number of samples to return (after optional burn-in)
// burnin: number of initial iterations to discard
std::vector<double> sampleMetropolis(const std::function<double(double)> &func,
									 double x0,
									 double sig,
									 double rMin,
									 double rMax,
									 int nSamples,
									 int burnin = 0);

void doRecursiveMetropolis(const std::function<double(double)> &func, std::vector<double> &results, double xi, double rMax, double rMin, int nSamples);
std::vector<double> recursiveMetropolis(const std::function<double(double)> &func, double xi, double rMin, double rMax, int nSamples);
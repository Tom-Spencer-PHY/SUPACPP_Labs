#include <iostream>
#include <vector>
#include <cmath>

float vec_mag(float x, float y){
    float xy_mag = std::sqrt(pow(x,2) + pow(y,2));
    return xy_mag;
}

int main (){
    std::cout << "Hello World" << std::endl;
    float x = 7.5;
    float y = 3.4;
    float xy_mag;
    std::vector<float> xy_vector = {x,y};
    xy_mag = std::sqrt(pow(xy_vector[0],2) + pow(xy_vector[1],2));
    std::cout << "xy_mag: " << xy_mag << std::endl;

    std::cout << "Enter x component" << std::endl;
    std::cin >> x;
    std::cout << "Enter y component" << std::endl;
    std::cin >> y;
    std::cout << "User vector magnitude: " << vec_mag(x,y) << std::endl;
}
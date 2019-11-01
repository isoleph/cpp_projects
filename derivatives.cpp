// g++ --std=c++17 -o deriv derivatives.cpp
/****************************************************
* Name: derivatives.cpp								*
* Description: A script to solve for derivatives at *
*   a point using limits                            *
* Supports:                                         *
*   - Stuff	                                        *
* Author: Angel A. Valdenegro                       *
* TODO: More tests with different functions         *
*****************************************************/ 

#include <iostream>
#include <cmath>
#include <functional>


double myFunction(double x) {
    return sin(x);
}

namespace dq {
    // definiton of the first derivative numerically
    double derivative(double x, std::function<double (double)> func) {
        constexpr const double increment = 0.00001;
        return (func(x + increment) - func(x))/(increment);
    }

    // definition of the secodn derivative numerically
    double secondDerivative(double x, std::function<double (double)> func) {
        constexpr const double increment = 0.00001;
        constexpr const double increment2 = 0.000000001;
        return (func(x + 2*increment) - 2*func(x + increment) + func(x))/(increment2);
    }
}


int main() {
    constexpr const double myPoint = 3.14159/4;
    std::cout << "Derivative at x: " << dq::derivative(myPoint, myFunction) << std::endl;
    std::cout << "Cosine at x: " << cos(myPoint) << std::endl;
    std::cout << "Negative Second Derivative at x: " << dq::secondDerivative(myPoint, myFunction) << std::endl;
    return 0;
}

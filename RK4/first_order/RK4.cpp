// g++ -std=c++17 -o RK4 RK4.cpp
/****************************************************
* Name: RK4.cpp									    *
* Description: A script to solve ODEs using the     *
*   Runge-Kutta Method                              *
* Supports:                                         *
*   - First-order solutions                         *
* Author: Angel A. Valdenegro                       *
* TODO: More tests with different functions         *
*****************************************************/ 

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <functional>


// create shorthand for types later 
typedef std::function<double (double, double)> function;
typedef std::vector<double> vector;


// test function
inline double myFunction(double x, double y) {
    return y;
}

// R-K Class where the magic happens
class RK4 {
    private: 
        //**Runge-Kutta Numbers to be saved incrementally**//
        double k1n, k2n, k3n, k4n;

        //** Functions to calculate the Runge-Kutta Numbers**//
        inline double k1 (double t, double y, double h, function func) {           // k1n
            k1n = h * func(t, y);
            return k1n;
        }
        inline double k2 (double t, double y, double h, function func) {           // k2n
            k2n = h * func(t + h/2, y + k1n/2);
            return k2n;
        }
        inline double k3 (double t, double y, double h, function func) {           // k3n
            k3n = h * func(t + h/2, y + k2n/2);
            return k3n;
        }
        inline double k4 (double t, double y, double h, function func) {           // k4n
            k4n = h * func(t + h, y + k3n);
            return k4n;
        }
    public:
        vector xvalues;
        vector yvalues;

        //**Solve for the values of the solution y thorough iteration **//
        // initial t-value t_0, final t-value t_f, initial y-value y_0, numbers of steps n
        vector iterator(double t_0, double t_f, double y_0, int n = 100, function func = myFunction) {

            double h = (t_f - t_0)/n;           // calculate incremental distances
            double y_n = y_0;                   // start solutions at y_0
            vector xpoints;                     // keep track of x-coordinates
            vector ypoints;                     // array to save solutions


            for(int i = 0; i <= n; i++) {
                double increment = h * i;
                xpoints.push_back(t_0 + increment);
                ypoints.push_back(y_n);

                y_n += 0.166667 * ( k1(t_0 + increment, y_n, h, func) + 2 * k2(t_0 + increment, y_n, h, func) 
                    + 2 * k3(t_0 + increment, y_n, h, func) + k4(t_0 + increment, y_n, h, func) );
            }
            xvalues = xpoints;
            yvalues = ypoints;

            return yvalues;
        }
};


// create csv with rk4 solution
int main() {
    RK4 object;
    // remember proper initial conditions
    vector results = object.iterator(0, 5, 1, 100, myFunction);

    std::ofstream outfile;
    outfile.open("RK4.csv");

    for (int i = 0; i < results.size(); i++) {
        outfile << object.xvalues[i] << ", " <<  object.yvalues[i] << std::endl;
    }
    outfile.close();
    return 0;
}



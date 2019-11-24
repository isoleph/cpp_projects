// g++ -std=c++17 -o RK42D RK42D.cpp
/****************************************************
* Name: RK42D.cpp									*
* Description: A script to solve 2-order ODEs       * 
*   using the Runge-Kutta Method                    *
* Supports:                                         *
*   - Second-order solutions                        *
* Author: Angel A. Valdenegro                       *
* TODO: More tests with different functions         *
*****************************************************/ 

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <functional>


// create shorthand for types later 
#define pi 3.14159265
typedef std::function<double (double, double, double)> function;
typedef std::vector<double> vector;


// test function
inline double myFunction(double x, double y, double yd) {
    return (-1 * y);
}

// R-K Class where the magic happens
class RK4 {
    private: 

        // Store RK4 numbers
        double k1n, k2n, k3n, k4n;          // First-Order Runge-Kutta Numbers
        double c1n, c2n, c3n, c4n;          // Define Second-Order Runge-Kutta Numbers


        //** Functions to calculate Second-Order RK Numbers **//
        inline double c1 (double ydn, double h) {                                              // c1n
            c1n = ydn;
            return c1n;
        }
        inline double c2 (double ydn, double h) {                                              // c2n
            c2n = ydn + 0.5 * h * k1n;
            return c2n;
        }
        inline double c3 (double ydn, double h ) {                                             // c3n
            c3n = ydn + 0.5 * h * k2n;
            return c3n;
        }
        inline double c4 (double ydn, double h) {                                              // c4n
            c4n = ydn + h * k3n;
            return c4n;
        }


        //** Functions to calculate First-Order RK Numbers**//
        inline double k1 (double t, double y, double ydn, double h, function func) {           // k1n
            k1n = func(t, y, ydn);
            return k1n;
        }
        inline double k2 (double t, double y, double ydn, double h, function func) {           // k2n
            k2n = func(t + h/2, y + h/2 * c1(ydn, h), ydn);
            return k2n;
        }
        inline double k3 (double t, double y, double ydn, double h, function func) {           // k3n
            k3n = func(t + h/2, y + h/2 * c2(ydn, h), ydn);
            return k3n;
        }
        inline double k4 (double t, double y, double ydn, double h, function func) {           // k4n
            k4n = func(t + h, y + h * c3(ydn, h), ydn);
            return k4n;
        }

    public:
        // Store values in an array if needed later 
        vector xvalues;
        vector yvalues;

        // initial t-value t_0, final t-value t_f, initial y-value y_0, numbers of steps n
        vector iterator(double t_0, double t_f, double y_0, double yd_0, int n = 100, function func = myFunction) {

            double h = (t_f - t_0)/n;           // calculate incremental distances
            double y_n = y_0;                   // initial y value
            double yd_n = yd_0;                 // initial y' value

            vector xpoints;                     // keep track of x-coordinates
            vector ypoints;                     // array to save solutions

            for(int i = 0; i <= n; i++) {
                double increment = h * i;
                xpoints.push_back(t_0 + increment);
                ypoints.push_back(y_n);

                yd_n += 0.166667 * h * ( 
                        k1(t_0 + increment, y_n, yd_n, h, func)
                  + 2 * k2(t_0 + increment, y_n, yd_n, h, func) 
                  + 2 * k3(t_0 + increment, y_n, yd_n, h, func) 
                      + k4(t_0 + increment, y_n, yd_n, h, func) 
                );

                y_n += h * (yd_n + h * 0.166667 * (
                        c1(yd_n, h)
                  + 2 * c2(yd_n, h)
                  + 2 * c3(yd_n, h)
                      + c4(yd_n, h)
                    )
                );
            }

            xvalues = xpoints;
            yvalues = ypoints;
            return yvalues;
        }
};


// create csv with numerical solution
int main() {
    RK4 object;
    // remember proper initial conditions!!
    vector results = object.iterator(0, 2 * pi, 0, 1, 500, myFunction);

    std::ofstream outfile;
    outfile.open("RK42O.csv");
    for (int i = 0; i < results.size(); i++) {
        outfile << object.xvalues[i] << ", " <<  object.yvalues[i] << std::endl;
    }
    outfile.close();
    return 0;
}



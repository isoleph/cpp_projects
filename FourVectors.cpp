/****************************************************
* Name: FourVectors.cpp                             *
* Description: C++ module for Lorentz Four Vectors  *
*     in Physics                                    *
* Supports:                                         *
*   - Addition                                      *
*   - Transposes                                    *
*   - Multiplication                                *
*   - Lorentz Boosts                                *
*   - Magnitudes                                    *
* Author: Angel A. Valdenegro                       *
* TODO: Implement index reassignments               *
*****************************************************/ 

#include <iostream>
#include <cmath> 
#include <vector>

class tensor {
    private: 
        // private data types
        std::vector<double> vec;            // vector
        std::vector<double> vecT;           // dual w. Minkowski (-+++)
        std::vector<double> current;        // current (dual/regular)

        // vector properties
        double mag;
        bool is_transpose = false;

    public:
        // constructor
        tensor(double t, double x, double y, double z) {
            try {
                mag = pow(-t*t + x*x + y*y + z*z, 0.5);
            } catch (const std::invalid_argument &ia) {
                std::cerr << "Invalid Argument: " << ia.what() << std::endl;
            }
            vec = {t, x, y, z};
            vecT = {-t, x, y, z};
            current = vec;
        }

        // allow indexing
        inline double& operator[](int s) {
            return vec[s];
        }
        // tranpose
        std::vector<double> T() {
            is_transpose = (is_transpose)? false : true;
            current = (is_transpose)? vecT : vec;
            return current;
        }
        // define vector addition operator
        tensor operator+(tensor &obj) {
            if (is_transpose != obj.is_transpose) {
                throw std::invalid_argument("Vectors are not addable.");
            }
            double rt = current[0] + obj[0]; 
            double rx = current[1] + obj[1]; 
            double ry = current[2] + obj[2]; 
            double rz = current[3] + obj[3];

            tensor result(rt, rx, ry, rz);
            return result;
        } 
        // define vector multiplication operator
        double operator*(tensor &obj) {
            if (is_transpose == obj.is_transpose) {
                throw std::invalid_argument("Vectors are not multiplicable.");
            }
            double result = 0;
            for (int i = 0; i < 4; i++) {
                result += current[i] * obj.current[i];
            }
            return result;
        }
        // define equating two four vectors 
        inline tensor& operator= (const tensor&);

        // reindexing 
        double& operator[](int i)

        // define Boosts on index with Beta value
        double Boost(int index=1, double B=0) {
            if (index == 0 || index > 3 ) {
                throw std::invalid_argument("Invalid index.");
            }
            double gamma = 1/pow(1 - B*B, 0.5);
            vec[index] = vec[index] * gamma;
            vecT[index] = vecT[index] * gamma;
            current[index] = current[index] * gamma;
            mag = pow(-current[0]*current[0] + current[1]*current[1]
                    + current[2]*current[2] + current[3]*current[3], 0.5);
            return 0;
        }
        // print vector to console
        inline int Print() {
            if (is_transpose) {
                printf("{%f, %f, %f, %f}<-(T)\n" , current[0], current[1], current[2], current[3]);
            } else {
                printf("{%f, %f, %f, %f}\n" , current[0], current[1], current[2], current[3]);
            }
            return 0;
        }
        // print magnitude to console
        inline double M() {
            std::cout << mag << std::endl;
            return mag;
        }
        // same as above but squared
        inline double M2() {
            double square = mag*mag;
            std::cout << square << std::endl;
            return square;
        }
};


// show examples with main
int main() {
    std::cout << "Initializing vectors.\n" << std::endl;
    tensor one(4, 5, 6, 5); tensor two = one;
    std::cout << "Vector A: " << std::endl;
    one.Print();
    std::cout << "Vector B: " << std::endl;
    two.Print();

    std::cout << "\nTransposing Vector B: " << std::endl;
    two.T();                                            // transpose
    two.Print();
    std::cout << "\nBoosting Vector B's x-coord: " << std::endl;
    two.Boost(1, 0.99);                                 // Boost x value
    two.Print();

    // multiply
    std::cout << "\n Multiplying A & B: " << std::endl;
    std::cout << one*two << std::endl;      // print contraction

    std::cout << "\n Transposing Vector B back:" << std::endl;
    two.T();
    two.Print();

    // add
    std::cout << "\n Adding A & B: " << std::endl;
    tensor three = one + two;
    three.Print();
    return 0;
}

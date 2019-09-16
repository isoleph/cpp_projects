#include <cmath>
#include <iostream>
#include <vector>

class tensor {
    private:
        // private values
        bool is_transpose = false;
        double Mag;
    public:
        // public values
        float ut, ux, uy, uz;

        //*** public member functions ***//
        // create vector with entries
        std::vector<double> r1(double t, double x, double y, double z) {
            try {
                Mag = pow(-t*t + x*x + y*y + z*z, 0.5);
            } catch (const std::invalid_argument &ia) {
                std::cerr << "Invalid Argument: " << ia.what() << std::endl;
            }
            // reassign public values; make vector
            ut = t; ux = x; uy = y; uz = z;
            std::vector<double> v{ut, ux, uy, uz};
            return v;
        }
        // creates a dual vector using Minkowski metric -+++
        std::vector<double> T() {
            std::vector<double> v = r1(-ut, ux, uy, uz);
            if (is_transpose) {
                is_transpose = false;
                return v;
            } else {
                is_transpose = true;
                return v;
            }
        }
        // print out entries in vector
        int Print() {
            printf("{%f, %f, %f, %f}", ut, ux, uy, uz);
            if (is_transpose == true) {std::cout << "††";}
            std::cout << std::endl;
            return 0;
        }
        // print magnitude of vector
        double M() {
            printf("%f\n", Mag);
            return Mag;
        }
        // define boost method
        std::vector<double> Boost(double B) {
            ux = ux / pow(1-B*B, 0.5);
            std::vector<double> v = r1(ut, ux, uy, uz);
            return v;
        }
        // define indexing operator
        double& operator[](int i) {
            std::vector<double> elem{ut,ux,uy,uz};
            return elem[i];
        }
        // define addition operator
        tensor operator+ (tensor const &obj) {
            if (is_transpose != obj.is_transpose) {
                throw std::invalid_argument("Vectors are not addable.");
            } 
            tensor a;
            a.ut = ut+ obj.ut; a.ux = ux + obj.ux;
            a.uy = uy+ obj.uy; a.uz = uz + obj.uz;
             a.Mag = pow(-a.ut*a.ut + a.ux*a.ux + a.uy*a.uy + \
                a.uz* a.uz, 0.5);
            return a;
        }
        // define multiplication operator
        double operator* (tensor &obj) {
            if (is_transpose == obj.is_transpose) {
                throw std::invalid_argument("Vectors are not multiplicable.");
            }
            tensor a;
            double multiple = (ut * obj.ut) + (ux * obj.ux) + \
                (uy * obj.uy) + (uz * obj.uz);
            return multiple;
        }
};

int main() {
    // initiate four vectors
    tensor mu; tensor nu; tensor alpha;
    std::vector<double> v = mu.r1(1, 2, 3, 4);
    std::vector<double> w = nu.r1(4,3,2,1);

    // assign four vectors
    std::cout << "Assigning Vectors Mu and Nu: " << std::endl;
    mu.Print();
    nu.Print();
    std::cout << std:: endl;
    // boost example
    std::cout << "Boosting Vector Mu:" << std::endl;
    mu.Boost(0.9999);
    mu.Print();
    std::cout << std::endl;
    // multiplcation example
    mu.T();
    std::cout << "Multiplying Mu by Nu:" << std::endl;
    std::cout << mu * nu << std::endl;
    mu.T();
    std::cout << std::endl; 
    // addition example
    std::cout << "Adding Mu and Nu: " << std::endl;
    alpha = mu + nu;
    alpha.Print();

    std::cout << "\nMagnitude of above: " << alpha.M() << std::endl;
    std::cout << "X component: " << mu[1] << std::endl;
    return 0;
}

#include <cmath>
#include "univers.hxx"

int main() {

    double r = 1;
    double sigma = 1;
    double epsilon = 1;
    double U_r = 4*epsilon*(pow((sigma/r), 12) - pow((sigma/r), 6));

    std::cout << U_r << std::endl;

    return 0;
}
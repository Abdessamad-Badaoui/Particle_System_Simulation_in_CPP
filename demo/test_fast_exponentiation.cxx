#include <iostream>
#include "fast_exponentiation.hxx"

int main(void) {

    double base = 2.5;
    int power = 3;
    
    double result = fast_exponentiation(base, power);

    std::cout << result << std::endl;

    return 0;
}
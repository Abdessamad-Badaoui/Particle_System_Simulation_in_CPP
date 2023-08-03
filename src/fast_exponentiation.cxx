#include "fast_exponentiation.hxx"

double fast_exponentiation(double x, int y) {
    if (y == 0) {
        return 1;
    } else if (y == 1) {
        return x;
    }

    double res_inter = fast_exponentiation(x, y/2);

    if (y % 2 == 0) {
        return res_inter * res_inter;
    } else {
        return x * res_inter * res_inter;
    }
}
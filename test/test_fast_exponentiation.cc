#include "fast_exponentiation.hxx"
#include <gtest/gtest.h>
#include <random>

TEST(TestFastExponentiation, TestSquaredErrorPow) {
    std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> base(-5.0, 5.0);
    
    double error = 0;
    for (int i = 1; i < 20; i++) {
        double x = base(rd);
        error += (fast_exponentiation(x, i) - pow(x, i))*(fast_exponentiation(x, i) - pow(x, i));
    }
    error = sqrt(error)/19;

    EXPECT_LE(error, 1e-2) << "L'algorithme de l'exponentiation rapide donne une erreur quadratique moyenne supérieure à 1e-2 en comparaison à la fonction pow(x, y), ce sur 19 réels tirée aléatoirement sur [-5.0, 5.0] et pour des puissances entières dans {1, ..., 19}";
}
#include "point.hxx"
#include <gtest/gtest.h>

TEST(TestPoint, Addition) {
    Point x(1, 2, 3);
    Point y(4, 5, 6);
    Point z = x + y;
    EXPECT_EQ(z(0), 5.0) << "z = x + y mais z[0] ≠ x[0] + y[0]";
    EXPECT_EQ(z(1), 7.0) << "z = x + y mais z[1] ≠ x[1] + y[1]";
    EXPECT_EQ(z(2), 9.0) << "z = x + y mais z[2] ≠ x[2] + y[2]";
}

TEST(TestPoint, ProduitParScalaireDroite) {
    double alpha = 0.5;
    Point x(2, 10, 100);
    Point y = x*alpha;
    EXPECT_EQ(y(0), 1.0) << "y = x*0.5 mais y[0] ≠ 0.5*x[0]";
    EXPECT_EQ(y(1), 5.0) << "y = x*0.5 mais y[1] ≠ 0.5*x[1]";
    EXPECT_EQ(y(2), 50.0) << "y = x*0.5 mais y[2] ≠ 0.5*x[2]";
}

TEST(TestPoint, Affectation) {
    Point x(1.0, 2.5, 3.1);
    Point y(0, 0, 0);
    Point z(0, 0, 0);
    z = (y = x);
    EXPECT_EQ(y(0), x(0)) << "Le Point x est affecte au Point y mais y[0] ≠ x[0]";
    EXPECT_EQ(y(1), x(1)) << "Le Point x est affecte au Point y mais y[1] ≠ x[1]";
    EXPECT_EQ(y(2), x(2)) << "Le Point x est affecte au Point y mais y[2] ≠ x[2]";
    EXPECT_EQ(z(0), x(0)) << "Le résultat de l'affectation du Point x à y est lui-même affecté au Point z (z = (y = x)) mais z[0] ≠ x[0]";
    EXPECT_EQ(z(1), x(1)) << "Le résultat de l'affectation du Point x à y est lui-même affecté au Point z (z = (y = x)) mais z[1] ≠ x[1]";
    EXPECT_EQ(z(2), x(2)) << "Le résultat de l'affectation du Point x à y est lui-même affecté au Point z (z = (y = x)) mais z[2] ≠ x[2]";
}

TEST(TestPoint, PlusEqual) {
    Point x(1, 2, 3);
    Point y(0.5, 1.5, 2.5);
    Point z(0, 0, 0);
    z = (x += y);
    EXPECT_EQ(x(0), 1.5) << "Le résultat de l'opération d'addition et d'affectation n'est pas correct pour la première coordonnée";
    EXPECT_EQ(x(1), 3.5) << "Le résultat de l'opération d'addition et d'affectation n'est pas correct pour la deuxième coordonnée";
    EXPECT_EQ(x(2), 5.5) << "Le résultat de l'opération d'addition et d'affectation n'est pas correct pour la troisième coordonnée";
    EXPECT_EQ(z(0), x(0)) << "Le résultat de l'opération d'addition et d'affectation n'est pas correct pour la première coordonnée du Point z";
    EXPECT_EQ(z(1), x(1)) << "Le résultat de l'opération d'addition et d'affectation n'est pas correct pour la deuxième coordonnée du Point z";
    EXPECT_EQ(z(2), x(2)) << "Le résultat de l'opération d'addition et d'affectation n'est pas correct pour la troisième coordonnée du Point z";
}

TEST(TestPoint, TimesEqual) {
    Point x(1, 2, 3);
    double alpha = 0.5;
    Point z(0, 0, 0);
    z = (x *= alpha);
    EXPECT_EQ(x(0), 0.5) << "L'opérateur *= ne fonctionne pas correctement sur la coordonnée x";
    EXPECT_EQ(x(1), 1.0) << "L'opérateur *= ne fonctionne pas correctement sur la coordonnée y";
    EXPECT_EQ(x(2), 1.5) << "L'opérateur *= ne fonctionne pas correctement sur la coordonnée z";
    EXPECT_EQ(z(0), x(0)) << "L'opérateur *= ne fonctionne pas correctement, le résultat n'est pas affecté à z[0]";
    EXPECT_EQ(z(1), x(1)) << "L'opérateur *= ne fonctionne pas correctement, le résultat n'est pas affecté à z[1]";
    EXPECT_EQ(z(2), x(2)) << "L'opérateur *= ne fonctionne pas correctement, le résultat n'est pas affecté à z[2]";
}

TEST(TestPoint, OutputStream) {
    std::stringstream buffer;
    std::streambuf* oldStdout = std::cout.rdbuf(buffer.rdbuf());

    Point x(1.5, 2.1, 3.4);
    std::cout << x;

    std::string output = buffer.str();
    std::cout.rdbuf(oldStdout);

    EXPECT_EQ("1.5 2.1 3.4 ", output) << "L'opérateur de flux << ne fonctionne pas pour la classe Point";
}
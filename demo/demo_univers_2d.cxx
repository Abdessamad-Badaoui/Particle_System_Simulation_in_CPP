#include <cmath>
#include "univers.hxx"

int main(void) {
    
    double sigma = 1;
    double epsilon = 5;
    double r_cut = 2.5*sigma;
    Univers my_univers(2, r_cut, Point(10, 10, 0));

    Particule *particle1 = new Particule(Point(-3, -2, 0), Point(0, 0, 0), 1, 2, 0);
    Particule *particle2 = new Particule(Point(-1, 0, 0), Point(-4, -4, 0), 1, 2, 1);
    Particule *particle3 = new Particule(Point(1, 2, 0), Point(0, 0, 0), 1, 2, 2);
    
    my_univers.add_particle(particle1);
    my_univers.add_particle(particle2);
    my_univers.add_particle(particle3);

    my_univers.evolve_potentiel(0.00005, 1, sigma, epsilon, false);

    return EXIT_SUCCESS;
}
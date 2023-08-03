#include "univers.hxx"
#include <random>
#include <cmath>

int main() {
    Particule *soleil = new Particule(Point(0, 0, 0), Point(0, 0, 0), 1, 2, 0);
    Particule *terre = new Particule(Point(0, 1, 0), Point(-1, 0, 0), 3e-6, 2, 1);
    Particule *jupiter = new Particule(Point(0, 5.36, 0), Point(-0.425, 0, 0), 9.55e-4, 2, 2);
    Particule *haley = new Particule(Point(34.75, 0, 0), Point(0, 0.0296, 0), 1e-14, 2, 3);
    Univers univers = Univers(2, 30, Point(30, 30, 0));

    univers.add_particle(soleil);
    univers.add_particle(terre);
    univers.add_particle(jupiter);
    univers.add_particle(haley);

    // std::random_device rd;
	// std::mt19937 mt(rd());
	// std::uniform_real_distribution<double> dist(0.0, 1.0);
    // std::uniform_real_distribution<double> mass(0.5, 0.6);

    // for (int i = 0; i < pow(2,6); i++) {
    //     Point position(dist(rd), dist(rd), dist(rd));
    //     Point vitesse(dist(rd), dist(rd), dist(rd));
    //     Point force(0, 0, 0);
    //     Point force_old(0, 0, 0);
    //     double masse = mass(rd);
    //     int dim = 3;
    //     int id = i;
    //     int categorie = 0;
    //     bool active = true;
    //     Particule *particle = new Particule{position, vitesse, force, force_old, masse, dim, id, categorie, active};
    //     univers.add_particle(particle);
    // }

    univers.initialize_system();
    univers.evolve(0.015, 468);

    
    return 0;
}
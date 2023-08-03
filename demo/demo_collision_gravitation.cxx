#include <cmath>
#include "univers.hxx"

int main() {
    int dim = 2;
    double L_d0 = 250;
    double L_d1 = 180;
    double epsilon = 4; 
    double sigma = 1;
    double r_cut = 2.5*sigma;
    Univers my_univers(dim, r_cut, Point(L_d0, L_d1, 0));

    double masse = 1;
    double dist_particles = pow(2, 1.0/6)/sigma;

    int id_particle = 0;

    double r = 12;

    double x0 = -r, x1 = r;
    double y0 = -35+2*r, y1 = -35;
    double x = x0, y = y0;
    Point centre_cercle(0, -35 + r, 0);
    Point vitesse_haut(0, -50, 0);
    Point particle_position;
    Point position_to_cercle;
    while (y >= y1) {
        while (x <= x1) {
            particle_position = Point(x, y, 0);
            position_to_cercle = particle_position - centre_cercle;
            double rayon = 0;
            for (int i = 0; i < 3; i++) {
                rayon += position_to_cercle(i)*position_to_cercle(i);
            }
            if (rayon <= r*r ) {
                Particule *particle = new Particule(particle_position, vitesse_haut, masse, dim, id_particle);
                my_univers.add_particle(particle);
                id_particle++;
            }
            x += dist_particles;
        }
        y -= dist_particles;
        x = x0;
    }

    x0 = -70, x1 = 70;
    y0 = -90 + dist_particles + 40, y1 = -90 + dist_particles;
    x = x0;
    y = y0;
    Point vitesse_bas(0, 0, 0);
    while (y >= y1) {
        while (x <= x1) {
            particle_position = Point(x, y, 0);
            Particule *particle = new Particule(particle_position, vitesse_bas, masse, dim, id_particle);
            my_univers.add_particle(particle);
            id_particle++;
            x += dist_particles;
        }
        y -= dist_particles;
        x = x0;
    }

    // my_univers.generate_vtk_file(std::string("disque_vitesse.vtu"));

    my_univers.setG(-12);
    my_univers.evolve_potentiel(0.00005, 4, sigma, epsilon, true);
    
    return EXIT_SUCCESS;
}
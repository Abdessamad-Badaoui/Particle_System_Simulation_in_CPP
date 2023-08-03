#include <cmath>
#include "univers.hxx"
#include <random>
#include <fstream>

void affiche_voisins(Cellule *cellule, std::ostream& output_stream) {
    output_stream << cellule->getCentre() << " => ";
    for (Cellule *cellule_voisine : cellule->getVoisins()) {
        if (cellule_voisine != nullptr) {
            output_stream << cellule_voisine->getCentre() << "; ";
        }
    }
    output_stream << "FIN";
}

int main(void) {

    // Univers *univers_3d = new Univers(3, 1, Point(10, 10, 10));

    // for (std::vector<std::vector<Cellule*>> mat_cellules : dynamic_cast<Grille_3d *>(univers_3d->getGrid())->cells_) {
    //     for (std::vector<Cellule*> ligne_cellules : mat_cellules) {
    //         for (Cellule *cellule : ligne_cellules) {
    //             std::cout << cellule->getCentre() << " => ";
    //             for (Cellule* voisine : cellule->getVoisins()) {
    //                 if (voisine != nullptr) {
    //                     std::cout << voisine->getCentre() << "; ";
    //                 }
    //             }
    //             std::cout << "FIN" << std::endl;
    //         }
    //     }
    // }

    // Univers *univers_1d = new Univers(1, 1, Point(6, 0, 0));
    // // Particule *particle_at_centre = new Particule(Point(2.1, 0, 0), Point(0, 0, 0), .5, 1, 0);

    // // univers_1d->add_particle(particle_at_centre);

    // int L_d = (int) univers_1d->getLD().at(0);

    // Cellule *cellule;

    // for (int i = 0; i < L_d; i++) {
    //     cellule = univers_1d->getGrid()->getCell(i, 0, 0);
    //     std::cout << cellule->getCentre() << " => ";
    //     for (Cellule *cellule_voisine : cellule->getVoisins()) {
    //         if (cellule_voisine != nullptr) {
    //             std::cout << cellule_voisine->getCentre() << "; ";
    //         }
    //     }
    //     std::cout << "FIN" << std::endl;
    // }

    // Univers *univers_2d = new Univers(2, 1, Point(4, 4, 0));

    // int L_d0 = (int) univers_2d->getGrid()->getSize()(0);
    // int L_d1 = (int) univers_2d->getGrid()->getSize()(1);
    // int i, j;
    // Cellule *cellule;

    // i = 0;
    // j = 0;
    // cellule = univers_2d->getGrid()->getCell(i, j, 0);
    // std::cout << cellule->getCentre() << " => ";
    // for (Cellule *cellule_voisine : cellule->getVoisins()) {
    //     if (cellule_voisine != nullptr) {
    //         std::cout << cellule_voisine->getCentre() << "; ";
    //     }
    // }
    // std::cout << "FIN" << std::endl;

    // i = 0;
    // j = L_d1/2;
    // cellule = univers_2d->getGrid()->getCell(i, j, 0);
    // std::cout << cellule->getCentre() << " => ";
    // for (Cellule *cellule_voisine : cellule->getVoisins()) {
    //     if (cellule_voisine != nullptr) {
    //         std::cout << cellule_voisine->getCentre() << "; ";
    //     }
    // }
    // std::cout << "FIN" << std::endl;

    // i = L_d0/2;
    // j = L_d1/2;
    // cellule = univers_2d->getGrid()->getCell(i, j, 0);
    // std::cout << cellule->getCentre() << " => ";
    // for (Cellule *cellule_voisine : cellule->getVoisins()) {
    //     if (cellule_voisine != nullptr) {
    //         std::cout << cellule_voisine->getCentre() << "; ";
    //     }
    // }
    // std::cout << "FIN" << std::endl;

    // std::random_device rd;
	// std::mt19937 mt(rd());
	// std::uniform_real_distribution<double> coord(-5.0, 5.0);
    // std::uniform_real_distribution<double> mass(0.5, 0.6);

    // Univers *univers_2d = new Univers(2, 1, 10);
    
    // for (int i = 0; i < 100; i++) {
    //     Particule *particle_at_centre = new Particule(Point(coord(rd), coord(rd), 0), Point(0, 0, 0), mass(rd), 2, i);
    //     univers_2d->add_particle(particle_at_centre);
    // }
    
    // for (std::vector<Cellule*> ligne_cellules : univers_2d->grille_2d) {
    //     for (Cellule *cellule : ligne_cellules) {
    //         std::cout << cellule->centre_ << " => ";
    //         for (Particule *particle : cellule->particles_) {
    //             particle->affiche_position();
    //         }
    //         std::cout << "FIN" << std::endl;
    //     }
    // }

    // Univers *univers_3d = new Univers(3, 1, Point(4, 4, 4));

    // // for (int i = 0; i < 1000; i++) {
    // //     Particule *particle_at_centre = new Particule(Point(coord(rd), coord(rd), coord(rd)), Point(0, 0, 0), mass(rd), 3, i);
    // //     univers_3d->add_particle(particle_at_centre);
    // // }

    // int L_d0 = (int) univers_3d->getGrid()->getSize()(0);
    // int L_d1 = (int) univers_3d->getGrid()->getSize()(1);
    // int L_d2 = (int) univers_3d->getGrid()->getSize()(2);

    // Particule *particle = new Particule(Point(0.2, 0.2, 0.2), Point(0, 0, 0), 1, 3, 0);

    // univers_3d->add_particle(particle);

    // Cellule *cellule = univers_3d->getGrid()->getCell(L_d0/2, L_d1/2, L_d2/2);
    // std::cout << cellule->getCentre() << " => ";
    // for (Particule *particle : cellule->getParticles()) {
    //     std::cout << particle->getPosition() << "; ";
    // }
    // std::cout << std::endl;

    // particle->setPosition(Point(0.2, 0.2, 1.2));

    // univers_3d->update_position_logique_particules();


    // cellule = univers_3d->getGrid()->getCell(L_d0/2, L_d1/2, L_d2/2);
    // std::cout << cellule->getCentre() << " => ";
    // for (Particule *particle : cellule->getParticles()) {
    //     std::cout << particle->getPosition() << "; ";
    // }
    // std::cout << std::endl;
    

    // cellule = univers_3d->getGrid()->getCell(L_d0/2, L_d1/2, L_d2/2 + 1);
    // std::cout << cellule->getCentre() << " => ";
    // for (Particule *particle : cellule->getParticles()) {
    //     std::cout << particle->getPosition() << "; ";
    // }
    // std::cout << std::endl;


    // for (Particule *particle : cellule->getParticles()) {
    //     std::cout << particle->getPosition() << "; ";
    // }

    // std::cout << std::endl;



    // for (std::vector<std::vector<Cellule*>> mat_cellules : univers_3d->grille_3d) {
    //     for (std::vector<Cellule*> ligne_cellules : mat_cellules) {
    //         for (Cellule *cellule : ligne_cellules) {
    //             std::cout << cellule->centre_ << " => " << std::endl << "\t";
    //             for (Cellule *voisine : cellule->voisins_) {
    //                 if (voisine != nullptr) {
    //                     for (Particule *particle_voisin : voisine->particles_) {
    //                         particle_voisin->affiche_position();
    //                         std::cout << " ; ";
    //                     }
    //                     std::cout << "\n\t";
    //                 }
    //             }
    //             std::cout << "FIN" << std::endl;
    //         }
    //     }
    // }


    double sigma = 1;
    double epsilon = 5;
    double r_cut = 2.5*sigma;
    Univers my_univers(2, r_cut, Point(40, 30, 0));


    double distance_entre_blocs = 2;
    double distance_entre_particles = pow(2, 1.0/6)/sigma;

    int id_particule = 0;
    
    int number_particles_up = 6;
    int number_particles_down = 10;

    Point vitesse_particules_haut(0, 0, 0);
    for (int i = 0; i < number_particles_up; i++) {
        for (int j = 0; j < number_particles_up; j++) {
            Point particle_position(i*distance_entre_particles -number_particles_up*distance_entre_particles/2, j*distance_entre_particles + distance_entre_blocs, 0);
            Particule *particle = new Particule(particle_position, vitesse_particules_haut, 1, 2, id_particule);
            my_univers.add_particle(particle);
            id_particule++;
        }
    }

    Point vitesse_nulle = Point(0, 0, 0);
    for (int i = 0; i < number_particles_down; i++) {
        for (int j = 0; j < number_particles_up; j++) {
            Point particle_position(i*distance_entre_particles - number_particles_down*distance_entre_particles/2, -j*distance_entre_particles, 0);
            Particule *particle = new Particule(particle_position, vitesse_nulle, 1, 2, id_particule);
            my_univers.add_particle(particle);
            id_particule++;
        }
    }

    // Particule *particle1 = new Particule(Point(1, distance_entre_blocs, 0), Point(0, -1, 0), 1, 2, 0);
    // Particule *particle2 = new Particule(Point(1, 0, 0), Point(0, 0, 0), 1, 2, 1);

    // my_univers.add_particle(particle1);
    // my_univers.add_particle(particle2);

    // int status = my_univers.generate_vtk_file("etat_initial.vtu");
    // if (status) {
    //     return EXIT_FAILURE;
    // }

    my_univers.setG(-10);
    my_univers.evolve_potentiel(0.00005, 8, sigma, epsilon, true);
    
    return EXIT_SUCCESS;
}
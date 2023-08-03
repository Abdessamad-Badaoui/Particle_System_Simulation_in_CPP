#include "grille_1d.hxx"

Cellule* Grille_1d::getCell(int i, int j, int k) {
    if (i >= 0 && i < n_cd1) {
        return this->cells_.at(i);
    }
    else {
        return nullptr;
    }
}

void Grille_1d::initCells(const Point& universeSize, double r_cut) {
    double L_d0 = universeSize(0);
    for (int i = 0; i < n_cd1; i++) {
        Point centre((i + .5)*r_cut - L_d0/2, 0, 0);
        this->cells_.at(i) = new Cellule(1, r_cut, centre);
    }
}

void Grille_1d::set_number_of_cells(int n_cd1, int n_cd2, int n_cd3) {
    Grille::set_number_of_cells(n_cd1, n_cd2, n_cd3);
    this->cells_.resize(n_cd1, nullptr);
}

void Grille_1d::setVoisins(double r_cut) {
    for (int i = 0; i < n_cd1; i++) {
        this->cells_.at(i)->getVoisins().resize(3, nullptr);
        this->cells_.at(i)->getVoisins().at(1) = this->cells_.at(i);
        if (i >= 1) {
            this->cells_.at(i)->getVoisins().at(0) = this->cells_.at(i-1);
        }
        if (i < (n_cd1-1)) {
            this->cells_.at(i)->getVoisins().at(2) = this->cells_.at(i+1);
        }
    }
}

void Grille_1d::update_forces_potentielles(double sigma, double epsilon, double r_cut, bool gravite, bool reflect_potentiel, std::vector<double> L_d) {
    for (Cellule *cellule : this->cells_) {
        for (Particule *particle_to_update : cellule->getParticles()) {
            if (gravite) {
                        particle_to_update->reinitialiseForceGravitation(this->G);
            } 
            else {
                particle_to_update->reinitialiseForce();
            }
            for (Cellule *cellule_voisine : cellule->getVoisins()) {
                if (cellule_voisine != nullptr) {
                    for (Particule *particle_neighbor : cellule_voisine->getParticles()) {
                        if (particle_to_update->getId() != particle_neighbor->getId()) {
                            particle_to_update->updateForceChargee(*particle_neighbor, sigma, epsilon, r_cut);
                        }
                    }
                }
            }
            if (reflect_potentiel) {
                particle_to_update->appliqueChargeMur(sigma, epsilon, r_cut, L_d);
            }
        }
    }
}

void Grille_1d::add_particle(Particule *particle, int particle_index_i, int particle_index_j, int particle_index_k, double r_cut) {
    if (particle_index_i >= 0 && particle_index_i < n_cd1) {
        this->cells_.at(particle_index_i)->getParticles().push_back(particle);
    }
}

void Grille_1d::update_position_logique_particules(double L_d0, double L_d1, double L_d2, double r_cut) {
    for (int i = 0; i < n_cd1; i++) {
        Cellule *cellule = this->cells_.at(i);
        int index_in_cell = 0;
        for (Particule *particle_to_update : cellule->getParticles()) {
            double particule_x = particle_to_update->getPosition().val[0];
            int particle_index_i = (particule_x + L_d0/2) >= 0 ? (int) ((particule_x + L_d0/2)/r_cut) : (int) ((particule_x + L_d0/2)/r_cut) - 1;
            // std::cout << "particule " << particle_to_update->getId() << " : " << particule_x << " => " << particle_index_i << std::endl; 
            if (particle_index_i != i) {       
                if (particle_index_i >= 0 && particle_index_i < n_cd1) {
                    this->cells_.at(particle_index_i)->getParticles().push_back(particle_to_update);
                }
                cellule->getParticles().erase(cellule->getParticles().begin() + index_in_cell);
            }
            else {
                index_in_cell++;
            }
        }
    }

    // std::cout << n_cd1 << std::endl << std::endl;
    // for (int i = 0; i < n_cd1; i++) {
    //     Cellule *cellule = this->cells_.at(i);
    //     for (Particule *particle : cellule->getParticles()) {
    //         std::cout << cellule->getCentre() << " : " << i << " ; " << particle->getId() << " : " << particle->getPosition() << std::endl;
    //     }
    // }
}
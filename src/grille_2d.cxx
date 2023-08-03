#include "grille_2d.hxx"

Cellule* Grille_2d::getCell(int i, int j, int k) {
    if (i >= 0 && i < n_cd1 &&
        j >= 0 && j < n_cd2) {
        return this->cells_.at(i).at(j);
    }
    else {
        return nullptr;
    }
}

void Grille_2d::initCells(const Point& universeSize, double r_cut) {
    double L_d0 = universeSize(0);
    double L_d1 = universeSize(1);
    for (int i = 0; i < n_cd1; i++) {
        for (int j = 0; j < n_cd2; j++) {
            Point centre((i + .5)*r_cut - L_d0/2, (j + .5)*r_cut - L_d1/2, 0);
            this->cells_.at(i).at(j) = new Cellule(2, r_cut, centre);
        }
    }
}

void Grille_2d::set_number_of_cells(int n_cd1, int n_cd2, int n_cd3) {
    Grille::set_number_of_cells(n_cd1, n_cd2, n_cd3);
    this->cells_.resize(n_cd1, std::vector<Cellule*>(n_cd2, nullptr));
}

void Grille_2d::setVoisins(double r_cut) {
    for (int i = 0; i < n_cd1; i++) {
        for (int j = 0; j < n_cd2; j++) {
            this->cells_.at(i).at(j)->getVoisins().resize(9, nullptr);
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    if ((i+k >= 0) && (i+k < n_cd1) && (j+l >= 0) && (j+l < n_cd2)) {
                        this->cells_.at(i).at(j)->getVoisins().at((k+1)*3 + l + 1) = this->cells_.at(i+k).at(j+l);
                    }
                }
            }
        }
    }
}

void Grille_2d::update_forces_potentielles(double sigma, double epsilon, double r_cut, bool gravite, bool reflect_potentiel, std::vector<double> L_d) {
    for (std::vector<Cellule*> ligne_cellules : this->cells_) {
        for (Cellule *cellule : ligne_cellules) {
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
}

void Grille_2d::add_particle(Particule *particle, int particle_index_i, int particle_index_j, int particle_index_k, double r_cut) {
    if (particle_index_i >= 0 && particle_index_i < n_cd1 &&
        particle_index_j >= 0 && particle_index_j < n_cd2) {
            this->cells_.at(particle_index_i).at(particle_index_j)->getParticles().push_back(particle);
    }
}

void Grille_2d::update_position_logique_particules(double L_d0, double L_d1, double L_d2, double r_cut) {
    for (int i = 0; i < n_cd1; i++) {
        for (int j = 0; j < n_cd2; j++) {
            Cellule *cellule = this->cells_.at(i).at(j);
            int index_in_cell = 0;
            for (Particule *particle_to_update : cellule->getParticles()) {
                double particle_x = particle_to_update->getPosition().val[0];
                double particle_y = particle_to_update->getPosition().val[1];

                int particle_index_i = (particle_x + L_d0/2) >= 0 ? (int) ((particle_x + L_d0/2)/r_cut) : -1;
                int particle_index_j = (particle_y + L_d1/2) >= 0 ? (int) ((particle_y + L_d1/2)/r_cut) : -1;

                if (particle_index_i != i || particle_index_j != j) {
                    if (particle_index_i >= 0 && particle_index_i < n_cd1 &&
                        particle_index_j >= 0 && particle_index_j < n_cd2
                        ) {
                        this->cells_.at(particle_index_i).at(particle_index_j)->getParticles().push_back(particle_to_update);
                    }
                    cellule->getParticles().erase(cellule->getParticles().begin() + index_in_cell);
                }
                else {
                    index_in_cell++;
                }
            }
        }
    }
}
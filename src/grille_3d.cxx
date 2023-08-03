#include "grille_3d.hxx"

Cellule* Grille_3d::getCell(int i, int j, int k) {
    if (i >= 0 && i < n_cd1 &&
        j >= 0 && j < n_cd2 &&
        k >= 0 && k < n_cd3) {
        return this->cells_.at(i).at(j).at(k);
    }
    else {
        return nullptr;
    }
}

void Grille_3d::initCells(const Point& universeSize, double r_cut) {
    double L_d0 = universeSize(0);
    double L_d1 = universeSize(1);
    double L_d2 = universeSize(2);
    for (int i = 0; i < n_cd1; i++) {
        for (int j = 0; j < n_cd2; j++) {
            for (int k = 0; k < n_cd3; k++) {
                Point centre((i + .5)*r_cut - L_d0/2, (j + .5)*r_cut - L_d1/2, (k + .5)*r_cut - L_d2/2);
                this->cells_.at(i).at(j).at(k) = new Cellule(3, r_cut, centre);
            }
        }
    }
}

void Grille_3d::set_number_of_cells(int n_cd1, int n_cd2, int n_cd3) {
    Grille::set_number_of_cells(n_cd1, n_cd2, n_cd3);
    this->cells_.resize(n_cd1, std::vector<std::vector<Cellule*>>(n_cd2, std::vector<Cellule*>(n_cd3, nullptr)));
}

void Grille_3d::setVoisins(double r_cut) {
    for (int i = 0; i < n_cd1; i++) {
        for (int j = 0; j < n_cd2; j++) {
            for (int k = 0; k < n_cd3; k++) {
                this->cells_.at(i).at(j).at(k)->getVoisins().resize(27, nullptr);
                for (int m = -1; m < 2; m++) {
                    for (int n = -1; n < 2; n++) {
                        for (int o = -1; o < 2; o++) {
                            if ((i+m >= 0) && (i+m < n_cd1) && (j+n >= 0) && (j+n < n_cd2) && (k+o >= 0) && (k+o < n_cd3)) {
                                this->cells_.at(i).at(j).at(k)->getVoisins().at((m+1)*9 + (n+1)*3 + o + 1) = this->cells_.at(i+m).at(j+n).at(k+o);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Grille_3d::update_forces_potentielles(double sigma, double epsilon, double r_cut, bool gravite, bool reflect_potentiel, std::vector<double> L_d) {
    for (std::vector<std::vector<Cellule*>> mat_cellules : this->cells_) {
        for (std::vector<Cellule*> ligne_cellules : mat_cellules) {
            for (Cellule *cellule : ligne_cellules) {
                for (Particule *particle_to_update : cellule->getParticles()) {
                    if (gravite) {
                        particle_to_update->reinitialiseForceGravitation(this->G);
                    } 
                    else {
                        particle_to_update->reinitialiseForce();
                    }
                    particle_to_update->reinitialiseForce();
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
}

void Grille_3d::add_particle(Particule *particle, int particle_index_i, int particle_index_j, int particle_index_k, double r_cut) {
    if (particle_index_i >= 0 && particle_index_i < n_cd1 &&
        particle_index_j >= 0 && particle_index_j < n_cd2 &&
        particle_index_k >= 0 && particle_index_k < n_cd3) {
            this->cells_.at(particle_index_i).at(particle_index_j).at(particle_index_k)->getParticles().push_back(particle);
    }
}

void Grille_3d::update_position_logique_particules(double L_d0, double L_d1, double L_d2, double r_cut) {
    for (int i = 0; i < n_cd1; i++) {
        for (int j = 0; j < n_cd2; j++) {
            for (int k = 0; k < n_cd3; k++) {
                Cellule *cellule = this->cells_.at(i).at(j).at(k);
                int index_in_cell = 0;
                for (Particule *particle_to_update : cellule->getParticles()) {
                    double particle_x = particle_to_update->getPosition().val[0];
                    double particle_y = particle_to_update->getPosition().val[1];
                    double particle_z = particle_to_update->getPosition().val[2];

                    int particle_index_i = (particle_x + L_d0/2) >= 0 ? (int) ((particle_x + L_d0/2)/r_cut) : -1;
                    int particle_index_j = (particle_y + L_d1/2) >= 0 ? (int) ((particle_y + L_d1/2)/r_cut) : -1;
                    int particle_index_k = (particle_z + L_d2/2) >= 0 ? (int) ((particle_z + L_d2/2)/r_cut) : -1;
                    
                    if (particle_index_i != i || particle_index_j != j || particle_index_k != k) {
                        if (particle_index_i >= 0 && particle_index_i < n_cd1 &&
                            particle_index_j >= 0 && particle_index_j < n_cd2 &&
                            particle_index_k >= 0 && particle_index_k < n_cd3
                            ) {
                            this->cells_.at(particle_index_i).at(particle_index_j).at(particle_index_k)->getParticles().push_back(particle_to_update);
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
}
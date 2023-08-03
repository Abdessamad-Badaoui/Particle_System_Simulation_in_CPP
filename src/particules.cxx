#include <iostream>
#include <cmath>

#include "particules.hxx"

Particule::Particule(Point position, Point vitesse, double masse, int dim, int id) {
    this->position = position;
    this->vitesse = vitesse;
    this->masse = masse;
    this->dim = dim;
    this->id = id;
}

// Getters
Point Particule::getPosition() const {
    return position;
}

Point Particule::getVitesse() const {
    return vitesse;
}

Point Particule::getForce() const {
    return force;
}

Point Particule::getOldForce() const {
    return force_old;
}

double Particule::getMasse() const {
    return masse;
}

int Particule::getDim() const {
    return dim;
}

int Particule::getId() const {
    return id;
}

int Particule::getCategorie() const {
    return categorie;
}

bool Particule::isActive() const {
    return active;
}

// Setters
void Particule::setPosition(Point position) {
    this->position = position;
}

void Particule::setVitesse(Point vitesse) {
    this->vitesse = vitesse;
}

void Particule::setForce(Point force) {
    this->force = force;
}

void Particule::setOldForce(Point force_old) {
    this->force_old = force_old;
}

void Particule::setMasse(double masse) {
    this->masse = masse;
}

void Particule::updateForce(const Particule &p){
    ///  
    Point orientation;
    double r = 0;
    /// Calcul du vecteur orientation
    orientation = p.position - this->position;
    for(int k=0;k<dim; k++){
        r += orientation(k) * orientation(k);
    }
    double f = this->masse * p.masse / (r * std::sqrt(r));
    force = force + f * orientation;
}

void Particule::updateForceChargee(const Particule &p, double sigma, double epsilon, double r_cut) {
    Point orientation;
    double r = 0;
    orientation = p.position - this->position;
    for(int k = 0; k < dim; k++){
        r += orientation(k) * orientation(k);
    }

    double sqrt_r = sqrt(r);
    
    if (r <= r_cut*r_cut) {
        if (r > 1e-3) {
            double f = 4*epsilon*(12*fast_exponentiation(sigma, 12)/fast_exponentiation(sqrt_r, 14) - 6*fast_exponentiation(sigma, 6)/fast_exponentiation(sqrt_r, 8));
            force  = force - f * orientation;
        }
    }
}

void Particule::appliqueChargeMur(double sigma, double epsilon, double r_cut, std::vector<double> L_d) {
    Point distance_mur_droite;
    Point distance_mur_gauche;
    distance_mur_droite = Point(L_d[0]/2, L_d[1]/2, L_d[2]/2) - this->position;
    distance_mur_gauche = this->position + Point(L_d[0]/2, L_d[1]/2, L_d[2]/2);
    Point somme_forces_murs = Point(0, 0, 0);
    double threshold = pow(2, 1.0/6)*sigma;
    double f;
    double r;
    for (int i = 0; i < 3; i++) {
        if (abs(distance_mur_droite(i)) <= threshold && L_d[i] != 0 ) {
            r = distance_mur_droite(i);
            f = -24*epsilon/(2*r)*fast_exponentiation(sigma/(2*r), 6)*(1 - 2*fast_exponentiation(sigma/(2*r), 6));
            somme_forces_murs(i) = somme_forces_murs(i) - f; 
        }
        if (abs(distance_mur_gauche(i)) <= threshold && L_d[i] != 0) {
            r = distance_mur_gauche(i);
            f = -24*epsilon/(2*r)*fast_exponentiation(sigma/(2*r), 6)*(1 - 2*fast_exponentiation(sigma/(2*r), 6));
            somme_forces_murs(i) = somme_forces_murs(i) + f;
        }
    }
    this->force = this->force + somme_forces_murs;

}

void Particule::salvageOldForce() {
    force_old = force;
}

void Particule::advance_position(double dt){
    position = position + dt * (vitesse + dt * 0.5/masse *force);
}

void Particule::advance_position(double dt, LimitCondition condition, double L_d0, double L_d1, double L_d2) {
    Point new_position = this->position + dt * (vitesse + dt * 0.5/masse *force);
    double grandeur_univer[] = {L_d0, L_d1, L_d2};
    Point position_relative_univers = new_position + Point(L_d0/2, L_d1/2, L_d2/2);
    bool debordement_x = position_relative_univers(0) < 0 || position_relative_univers(0) >= L_d0;
    bool debordement_y = ((position_relative_univers(1) < 0 || position_relative_univers(1) >= L_d1) && (L_d1 != 0));
    bool debordement_z = ((position_relative_univers(2) < 0 || position_relative_univers(2) >= L_d2) && (L_d2 != 0));
    if (debordement_x || debordement_y || debordement_z) {
        switch (condition)
        {
            case LimitCondition::Absorption:
                this->position = new_position;
                this->force_old = Point(0, 0, 0);
                this->force = Point(0, 0, 0);
                break;
            case LimitCondition::Periodicity:
                for (int i = 0; i < 3; i++) {
                    if (grandeur_univer[i] > 0) {
                        new_position(i) = fmod(fmod(position_relative_univers(i), grandeur_univer[i]) + grandeur_univer[i], grandeur_univer[i]) - grandeur_univer[i]/2; 
                    }
                }
                this->position = new_position;
                break;
            case LimitCondition::Reflection: {
                int poids;
                if (debordement_x) {
                    poids = (int) (fmin(fmax(position_relative_univers(0), 0), L_d0)/L_d0);
                    this->position = (1 - poids) * Point(-L_d0 - new_position(0), this->position(1), this->position(2)) + poids * Point(L_d0 - new_position(0), this->position(1), this->position(2));
                    this->vitesse = Point(-this->vitesse(0), this->vitesse(1), this->vitesse(2));
                }
                if (debordement_y) {
                    poids = (int) (fmin(fmax(position_relative_univers(1), 0), L_d1)/L_d1);
                    this->position = (1 - poids) * Point(this->position(0), -L_d1 - new_position(1), this->position(2)) + poids * Point(this->position(0), L_d1 - new_position(1), this->position(2));
                    this->vitesse = Point(this->vitesse(0), -this->vitesse(1), this->vitesse(2));
                }
                if (debordement_z) {
                    poids = (int) (fmin(fmax(position_relative_univers(2), 0), L_d2)/L_d2);
                    this->position = (1 - poids) * Point(this->position(0), this->position(1), -L_d2 - new_position(2)) + poids * Point(this->position(0), this->position(1), L_d2 - new_position(2));
                    this->vitesse = Point(this->vitesse(0), this->vitesse(1), -this->vitesse(2));
                }
                break;
            }
        }
    }
    else {
        this->position = new_position;
    }
}

void Particule::advance_vitesse(double dt){
    vitesse = vitesse + dt * 0.5/masse*(force + force_old);
}

void Particule::reinitialiseForce() {
    force = Point(0, 0, 0);
}

void Particule::reinitialiseForceGravitation(double G) {
    force = Point(0, this->masse * G, 0);
}
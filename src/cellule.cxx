#include "cellule.hxx"

Cellule::Cellule(int dim, double arete, Point centre) {
    spaceDim_ = dim;
    arete_ = arete;
    centre_= centre;
}

int Cellule::getSpaceDim(){
    return spaceDim_;
}

void Cellule::setSpaceDim(int dim) {
    spaceDim_ = dim;
}

double Cellule::getArete(){
    return arete_;
}

void Cellule::setArete(double arete) {
    arete_ = arete;
}

Point Cellule::getCentre(){
    return centre_;
}

void Cellule::setCentre(Point centre) {
    centre_ = centre;
}

std::vector<Cellule*>& Cellule::getVoisins(){
    return voisins_;
}

void Cellule::setVoisins(std::vector<Cellule*> voisins) {
    voisins_ = voisins;
}

std::vector<Particule*>& Cellule::getParticles(){
    return particles_;
}

void Cellule::setParticles(std::vector<Particule*> particles) {
    particles_ = particles;
}
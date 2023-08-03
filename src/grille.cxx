#include "grille.hxx"


int Grille::get_ncd1() const{
    return n_cd1;
}

int Grille::get_ncd2() const{
    return n_cd2;
}

int Grille::get_ncd3() const{
    return n_cd3;
}

void Grille::set_number_of_cells(int n_cd1, int n_cd2, int n_cd3) {
    this->n_cd1 = n_cd1;
    this->n_cd2 = n_cd2;
    this->n_cd3 = n_cd3;
}

void Grille::setG(double G) {
    this->G = G;
}
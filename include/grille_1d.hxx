#pragma once
#include "grille.hxx"

/**
 * @brief Represents a 1D grid.
 */
class Grille_1d : public Grille {
    public:
        /**
         * @brief Get the cell at the specified indices.
         * @param i The index in dimension 1.
         * @param j The index in dimension 2. It is not considered in this case.
         * @param k The index in dimension 3. It is not considered in this case.
         * @return Pointer to the Cellule object.
         */
        Cellule* getCell(int i, int j, int k) override;

        /**
         * @brief Initialize the grid cells.
         * @param universeSize The size of the universe.
         * @param r_cut The cutoff distance.
         */
        void initCells(const Point& universeSize, double r_cut) override;

        /**
         * @brief Set the number of cells in each dimension.
         * @param n_cd1 Number of cells in dimension 1.
         * @param n_cd2 Number of cells in dimension 2.
         * @param n_cd3 Number of cells in dimension 3.
         */
        void set_number_of_cells(int n_cd1, int n_cd2, int n_cd3) override;

        /**
         * @brief Set the neighbors of each cell within the cutoff distance.
         * @param r_cut The cutoff distance.
         */
        void setVoisins(double r_cut) override;

        /**
         * @brief Update the forces and potentials for the particles.
         * @param sigma The Lennard-Jones potential parameter sigma.
         * @param epsilon The Lennard-Jones potential parameter epsilon.
         * @param r_cut The cutoff distance.
         * @param gravite Indicates if gravity is considered.
         * @param reflect_potentiel Indicates if potential reflection is enabled.
         * @param L_d The dimensions of the universe.
         */
        void update_forces_potentielles(double sigma, double epsilon, double r_cut, bool gravite, bool reflect_potentiel, std::vector<double> L_d) override;

        /**
         * @brief Add a particle to the grid.
         * @param particle The particle to add.
         * @param particle_index_i The index of the particle in dimension 1.
         * @param particle_index_j The index of the particle in dimension 2. It is not considered in this case.
         * @param particle_index_k The index of the particle in dimension 3. It is not considered in this case.
         * @param r_cut The cutoff distance.
         */
        void add_particle(Particule* particle, int particle_index_i, int particle_index_j, int particle_index_k, double r_cut) override;

        /**
         * @brief Update the logical positions of the particles within the grid.
         * @param L_d0 The size of the universe in dimension 0.
         * @param L_d1 The size of the universe in dimension 1. It is not considered in this case.
         * @param L_d2 The size of the universe in dimension 2. It is not considered in this case.
         * @param r_cut The cutoff distance.
         */
        void update_position_logique_particules(double L_d0, double L_d1, double L_d2, double r_cut) override;

    private:
        std::vector<Cellule*> cells_; /**< Vector of grid cells. */
};

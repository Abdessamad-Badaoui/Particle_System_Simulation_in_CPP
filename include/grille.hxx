#include "cellule.hxx"

/**
 * @brief Represents a grid.
 */
class Grille {
protected:
    int n_cd1; /**< Number of cells in dimension 1. */
    int n_cd2; /**< Number of cells in dimension 2. */
    int n_cd3; /**< Number of cells in dimension 3. */
    double G;  /**< Gravitational constant. */

public:
    /**
     * @brief Get the cell at the specified indices.
     * @param i The index in dimension 1.
     * @param j The index in dimension 2.
     * @param k The index in dimension 3.
     * @return Pointer to the Cellule object.
     */
    virtual Cellule* getCell(int i, int j, int k) = 0;

    /**
     * @brief Initialize the grid cells.
     * @param universeSize The size of the universe.
     * @param r_cut The cutoff distance.
     */
    virtual void initCells(const Point& universeSize, double r_cut) = 0;

    /**
     * @brief Set the neighbors of each cell within the cutoff distance.
     * @param r_cut The cutoff distance.
     */
    virtual void setVoisins(double r_cut) = 0;

    /**
     * @brief Update the forces and potentials for the particles.
     * @param sigma The Lennard-Jones potential parameter sigma.
     * @param epsilon The Lennard-Jones potential parameter epsilon.
     * @param r_cut The cutoff distance.
     * @param gravite Indicates if gravity is considered.
     * @param reflect_potentiel Indicates if potential reflection is enabled.
     * @param L_d The dimensions of the universe.
     */
    virtual void update_forces_potentielles(double sigma, double epsilon, double r_cut, bool gravite, bool reflect_potentiel, std::vector<double> L_d) = 0;

    /**
     * @brief Add a particle to the grid.
     * @param particle The particle to add.
     * @param particle_index_i The index of the particle in dimension 1.
     * @param particle_index_j The index of the particle in dimension 2.
     * @param particle_index_k The index of the particle in dimension 3.
     * @param r_cut The cutoff distance.
     */
    virtual void add_particle(Particule *particle, int particle_index_i, int particle_index_j, int particle_index_k, double r_cut) = 0;

    /**
     * @brief Update the logical positions of the particles within the grid.
     * @param L_d0 The size of the universe in dimension 0.
     * @param L_d1 The size of the universe in dimension 1.
     * @param L_d2 The size of the universe in dimension 2.
     * @param r_cut The cutoff distance.
     */
    virtual void update_position_logique_particules(double L_d0, double L_d1, double L_d2, double r_cut) = 0;

    /**
     * @brief Set the number of cells in each dimension.
     * @param n_cd1 Number of cells in dimension 1.
     * @param n_cd2 Number of cells in dimension 2.
     * @param n_cd3 Number of cells in dimension 3.
     */
    virtual void set_number_of_cells(int n_cd1, int n_cd2, int n_cd3) = 0;

    /**
     * @brief Get the number of cells in dimension 1.
     * @return The number of cells in dimension 1.
     */
    int get_ncd1() const;

    /**
     * @brief Get the number of cells in dimension 2.
     * @return The number of cells in dimension 2.
     */
    int get_ncd2() const;

    /**
     * @brief Get the number of cells in dimension 3.
     * @return The number of cells in dimension 3.
     */
    int get_ncd3() const;

    /**
     * @brief Set the gravitational constant.
     * @param G The gravitational constant.
     */
    void setG(double G);
};

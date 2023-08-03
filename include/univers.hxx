#pragma once
#include "grille_3d.hxx"
#include <assert.h>

/**
 * @class Univers
 * @brief Represents the universe that contains particles and a grid.
 *
 * The Univers class represents the universe that contains particles and a grid. It stores information about the particles,
 * dimensionality, cutoff radius, universe size, and gravitational constant. It also provides methods for evolving the system,
 * updating forces, initializing the system, and generating VTK files.
 */
class Univers {
    std::vector<Particule*> particles_collection;   ///< Collection of particles in the universe.
    int dim;                                       ///< Dimensionality of the universe.
    double r_cut;                                  ///< Cutoff radius.
    std::vector<double> L_d;                       ///< Dimensions of the universe.
    double G = -10;                                ///< Gravitational constant.
    Grille *grid_;                                 ///< Pointer to the grid object.

public:
    // Getters
    int getDim();
    double getRCut();
    std::vector<double>& getLD();
    Grille* getGrid();

    // Setters
    void setDim(int dim);
    void setRCut(double r_cut);
    void setLD(const std::vector<double>& l_d);
    void setG(double G);
    void initGridG();

    // Particle operations
    void add_particle(Particule* particle);

    /**
     * @brief Evolves the system over a specified duration using a default potential.
     *
     * This method evolves the system over a specified duration using a default potential. It updates the positions and velocities
     * of the particles based on the specified time step and the forces acting on them. The evolution process takes into account
     * gravitational forces if enabled.
     *
     * @param dt The time step for the evolution.
     * @param duree The duration of the evolution.
     */
    void evolve(double dt, double duree);

    /**
     * @brief Evolves the system over a specified duration using the Lennard-Jones potential.
     *
     * This method evolves the system over a specified duration using the Lennard-Jones potential. It updates the positions and
     * velocities of the particles based on the specified time step and the forces acting on them. The evolution process takes
     * into account gravitational forces if enabled, and uses the Lennard-Jones potential parameters sigma and epsilon.
     *
     * @param dt The time step for the evolution.
     * @param duree The duration of the evolution.
     * @param sigma The Lennard-Jones potential parameter sigma.
     * @param epsilon The Lennard-Jones potential parameter epsilon.
     * @param gravite Indicates if gravity is considered.
     */
    void evolve_potentiel(double dt, double duree, double sigma, double epsilon, bool gravite);

    /**
     * @brief Evolves the system over a specified duration using the Lennard-Jones potential without using the grid.
     *
     * This method evolves the system over a specified duration using the Lennard-Jones potential without using the grid. It
     * updates the positions and velocities of the particles based on the specified time step and the forces acting on them.
     * The evolution process uses the Lennard-Jones potential parameters sigma and epsilon.
     *
     * @param dt The time step for the evolution.
     * @param duree The duration of the evolution.
     * @param sigma The Lennard-Jones potential parameter sigma.
     * @param epsilon The Lennard-Jones potential parameter epsilon.
     */
    void evolve_potentiel_no_grille(double dt, double duree, double sigma, double epsilon);

    /**
     * @brief Initializes the system.
     *
     * This method initializes the system by setting up the grid and assigning particles to cells. It prepares the system for
     * further evolution and force calculations.
     */
    void initialize_system();

    /**
     * @brief Updates the gravitational forces acting on the particles.
     *
     * This method updates the gravitational forces acting on the particles in the system. It recalculates the forces based on the
     * current positions and masses of the particles.
     */
    void update_forces_gravitationnelle();

    /**
     * @brief Updates the Lennard-Jones forces acting on the particles without using the grid.
     *
     * This method updates the Lennard-Jones forces acting on the particles without using the grid. It recalculates the forces
     * based on the current positions and interactions between particles. The method uses the Lennard-Jones potential parameters
     * sigma and epsilon.
     *
     * @param sigma The Lennard-Jones potential parameter sigma.
     * @param epsilon The Lennard-Jones potential parameter epsilon.
     */
    void update_forces_potentielles_no_grille(double sigma, double epsilon);

    /**
     * @brief Updates the Lennard-Jones forces acting on the particles using the grid.
     *
     * This method updates the Lennard-Jones forces acting on the particles using the grid. It recalculates the forces based on
     * the current positions and interactions between particles within the cutoff distance. The method uses the Lennard-Jones
     * potential parameters sigma and epsilon. It also takes into account gravitational forces if enabled, and potential
     * reflection based on the specified conditions.
     *
     * @param sigma The Lennard-Jones potential parameter sigma.
     * @param epsilon The Lennard-Jones potential parameter epsilon.
     * @param gravite Indicates if gravity is considered.
     * @param reflect_potentiel Indicates if potential reflection is enabled.
     * @param L_d The dimensions of the universe.
     */
    void update_forces_potentielles_grille(double sigma, double epsilon, bool gravite, bool reflect_potentiel, std::vector<double> L_d);

    /**
     * @brief Updates the logical positions of the particles within the grid.
     *
     * This method updates the logical positions of the particles within the grid. It recalculates the indices of the cells
     * containing the particles based on their current positions.
     */
    void update_position_logique_particules();


    // VTK file generation
    int generate_vtk_file(const std::string& file_name);

    /**
     * @brief Constructs an Univers object with the specified parameters.
     * @param dimension The dimensionality of the universe.
     * @param rayon_coupure The cutoff radius.
     * @param grandeur_univers The size of the universe.
     */
    Univers(int dimension, double rayon_coupure, Point grandeur_univers);
};

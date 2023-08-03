#pragma once
#include <list>
#include <vector>
#include "point.hxx"
#include "fast_exponentiation.hxx"
#include "condition_limite.hxx"

/**
 * @class Particule
 * @brief Represents a particle with position, velocity, force, and other properties.
 */
class Particule {
private:
    Point position;     ///< The position of the particle.
    Point vitesse;      ///< The velocity of the particle.
    Point force;        ///< The force acting on the particle.
    Point force_old;    ///< The previous force acting on the particle.

    double masse;       ///< The mass of the particle.

    int dim;            ///< The dimensionality of the particle.
    int id;             ///< The identifier of the particle.
    int categorie;      ///< The category of the particle.
    bool active;        ///< The status of the particle.

public:
    // Getters
    Point getPosition() const;
    Point getVitesse() const;
    Point getForce() const;
    Point getOldForce() const;
    double getMasse() const;
    int getDim() const;
    int getId() const;
    int getCategorie() const;
    bool isActive() const;

    // Setters
    void setPosition(Point position);
    void setVitesse(Point vitesse);
    void setForce(Point force);
    void setOldForce(Point force_old);
    void setMasse(double masse);

    // Physics methods
    /**
	 * @brief Advances the position of the particle based on the given time step.
	 * @param dt The time step for the position update.
	 */
	void advance_position(double dt);

	/**
	 * @brief Advances the position of the particle based on the given time step and applies a limit condition.
	 * @param dt The time step for the position update.
	 * @param condition The limit condition for the position update.
	 * @param L_d0 The limit value for dimension 0.
	 * @param L_d1 The limit value for dimension 1.
	 * @param L_d2 The limit value for dimension 2.
	 */
	void advance_position(double dt, LimitCondition condition, double L_d0, double L_d1, double L_d2);

	/**
	 * @brief Advances the velocity of the particle based on the given time step.
	 * @param dt The time step for the velocity update.
	 */
	void advance_vitesse(double dt);

	/**
	 * @brief Updates the force acting on the particle based on the force exerted by another particle.
	 * @param other The other particle exerting the force.
	 */
	void updateForce(const Particule& other);

	/**
	 * @brief Saves the current force as the old force.
	 */
	void salvageOldForce();

	/**
	 * @brief Reinitializes the force acting on the particle.
	 */
	void reinitialiseForce();

	/**
	 * @brief Reinitializes the gravitational force acting on the particle with the given constant.
	 * @param G The gravitational constant.
	 */
	void reinitialiseForceGravitation(double G);

    // Additional methods
    void updateForceChargee(const Particule& other, double sigma, double epsilon, double r_cut);
    void appliqueChargeMur(double sigma, double epsilon, double r_cut, std::vector<double> L_d);

    /**
     * @brief Constructor for Particule class.
     * @param position The initial position of the particle.
     * @param vitesse The initial velocity of the particle.
     * @param masse The mass of the particle.
     * @param dim The dimensionality of the particle.
     * @param id The identifier of the particle.
     */
    Particule(Point position, Point vitesse, double masse, int dim, int id);
};

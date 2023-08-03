#pragma once
#include <vector>
#include "particules.hxx"

/**
 * @class Cellule
 * @brief Represents a cell within a grid (Grille).
 *
 * The Cellule class represents a cell within a grid (Grille). It contains information about the cell's properties,
 * such as its space dimension, edge length, center point, neighboring cells, and particles within the cell.
 */
class Cellule {
    int spaceDim_;                      ///< The space dimension of the cell.
    double arete_;                      ///< The length of the cell's edge.
    Point centre_;                      ///< The center point of the cell.
    std::vector<Cellule*> voisins_;     ///< The neighboring cells of the cell.
    std::vector<Particule*> particles_;  ///< The particles within the cell.

public:
    /**
     * @brief Constructs a Cellule object with the given parameters.
     * @param dim The space dimension of the cell.
     * @param arete The length of the cell's edge.
     * @param centre The center point of the cell.
     */
    Cellule(int dim, double arete, Point centre);

    // Getters and Setters
    int getSpaceDim();
    void setSpaceDim(int dim);
    double getArete();
    void setArete(double arete);
    Point getCentre();
    void setCentre(Point centre);
    std::vector<Cellule*>& getVoisins();
    void setVoisins(std::vector<Cellule*> voisins);
    std::vector<Particule*>& getParticles();
    void setParticles(std::vector<Particule*> particles);
};

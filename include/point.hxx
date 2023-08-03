#pragma once
#include<iostream>
#include <array>

/**
 * @class Point
 * @brief Represents a point in 3D space.
 */
class Point {
public:
    std::array<double, 3> val; ///< Contains the coordinates of the point.

    /**
     * @brief Default constructor.
     */
    Point();

    /**
     * @brief Copy constructor.
     * @param other The point to copy from.
     */
    Point(const Point& other);

    /**
     * @brief Constructor with initial coordinates.
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     * @param z The z-coordinate of the point.
     */
    Point(double x, double y, double z);

    /**
     * @brief Addition operator.
     * @param other The point to add.
     * @return The resulting point after addition.
     */
    Point operator+(const Point& other);

    /**
     * @brief Compound addition operator.
     * @param other The point to add.
     * @return Reference to the current point after addition.
     */
    Point& operator+=(const Point& other);

    /**
     * @brief Scalar multiplication operator.
     * @param scalar The scalar value to multiply.
     * @return The resulting point after multiplication.
     */
    Point operator*(double scalar);

    /**
     * @brief Compound scalar multiplication operator.
     * @param scalar The scalar value to multiply.
     * @return Reference to the current point after multiplication.
     */
    Point& operator*=(double scalar);

    /**
     * @brief Assignment operator.
     * @param other The point to assign.
     * @return Reference to the current point after assignment.
     */
    Point& operator=(const Point& other);

    /**
     * @brief Indexing operator for accessing coordinates.
     * @param index The index of the coordinate (0, 1, or 2).
     * @return Reference to the coordinate value.
     */
    double& operator()(int index);

    /**
     * @brief Indexing operator for accessing coordinates (const version).
     * @param index The index of the coordinate (0, 1, or 2).
     * @return The coordinate value.
     */
    double operator()(int index) const;

    /**
     * @brief Destructor.
     */
    ~Point();
};

/**
 * @brief Output stream operator for Point objects.
 * @param os The output stream.
 * @param point The Point object to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Point& point);

/**
 * @brief Scalar multiplication operator with a scalar value on the left-hand side.
 * @param scalar The scalar value to multiply.
 * @param point The Point object to multiply.
 * @return The resulting point after multiplication.
 */
Point operator*(double scalar, const Point& point);

/**
 * @brief Addition operator for two Point objects.
 * @param point1 The first Point object.
 * @param point2 The second Point object.
 * @return The resulting point after addition.
 */
Point operator+(const Point& point1, const Point& point2);

/**
 * @brief Subtraction operator for two Point objects.
 * @param point1 The first Point object.
 * @param point2 The second Point object.
 * @return The resulting point after subtraction.
 */
Point operator-(const Point& point1, const Point& point2);

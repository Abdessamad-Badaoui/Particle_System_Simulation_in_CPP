#ifndef LIMIT_CONDITIONS_HXX
#define LIMIT_CONDITIONS_HXX

/**
 * @enum LimitCondition
 * @brief Enumerates different limit conditions for particle movement.
 *
 * The LimitCondition enum represents different types of limit conditions that can be applied
 * to particle movement. It is used to specify how particles behave when they reach the boundaries
 * or limits of a system.
 */
enum class LimitCondition {
    Absorption,   ///< The particle is absorbed or disappears when it reaches the boundary.
    Periodicity,  ///< The system is periodic, and the particle reappears on the opposite side when it reaches the boundary.
    Reflection    ///< The particle reflects or bounces off the boundary when it reaches it.
};

#endif

%%writefile physics.hpp
#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "act_core.hpp"
#include <cmath>

namespace act {

/**
 * @brief Вычисляет локальный вклад в действие для тетраэдра
 * S_geom = sum(W_i * det(U_ij))
 */
double calculate_local_action(const Tetrahedron& tet, const Graph& G) {
    // Пока возвращаем упрощенный инвариант, 
    // позже сюда добавим тензорную кривизну
    return tet.W * 0.5; 
}

/**
 * @brief Пример функции для оценки состояния фермиона
 */
double estimate_psi_density(const Vertex& v) {
    double density = 0;
    for(int i = 0; i < 4; ++i) {
        density += std::norm(v.psi[i]);
    }
    return density;
}

} // namespace act

#endif // PHYSICS_HPP

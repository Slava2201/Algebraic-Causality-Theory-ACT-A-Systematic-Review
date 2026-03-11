%%writefile simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "act_core.hpp"
#include <random>

namespace act {

/**
 * @brief Попытка обновить состояние фермиона в случайной вершине
 * (Упрощенный алгоритм Метрополиса)
 */
void metropolis_step(Graph& G, double beta) {
    static std::mt19937 gen(42);
    static std::uniform_int_distribution<> d_vert(0, G.vertices.size() - 1);
    static std::uniform_real_distribution<> d_rand(0.0, 1.0);

    int v_idx = d_vert(gen);
    
    // 1. Запоминаем старое "действие" (упрощенно - плотность)
    double old_s = 0;
    for(int i=0; i<4; ++i) old_s += std::norm(G.vertices[v_idx].psi[i]);

    // 2. Делаем случайный "шаг" (меняем спинор)
    Complex shift(d_rand(gen) - 0.5, d_rand(gen) - 0.5);
    G.vertices[v_idx].psi[0] += shift;

    // 3. Считаем новое действие
    double new_s = 0;
    for(int i=0; i<4; ++i) new_s += std::norm(G.vertices[v_idx].psi[i]);

    // 4. Принимаем или отвергаем (пока простейшая логика минимизации)
    if (new_s > old_s && d_rand(gen) > std::exp(-beta * (new_s - old_s))) {
        G.vertices[v_idx].psi[0] -= shift; // Откатываем
    }
}

} // namespace act

#endif // SIMULATION_HPP

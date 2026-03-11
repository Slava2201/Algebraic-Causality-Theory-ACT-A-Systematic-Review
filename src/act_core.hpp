%%writefile act_core.hpp
#ifndef ACT_CORE_HPP
#define ACT_CORE_HPP

#include <vector>
#include <complex>

namespace act {

using Complex = std::complex<double>;

struct Vertex {
    int id;
    int octant;
    Complex tau[32];
    Complex psi[4];
    std::vector<int> tetrahedra;
};

struct Edge {
    int id;
    int v1, v2;
};

struct Tetrahedron {
    int id;
    int vertices[4];
    double W;
};

struct Graph {
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::vector<Tetrahedron> tetrahedra;
};

} // namespace act

#endif // ACT_CORE_HPP



%%writefile main.cpp
#include <iostream>
#include "act_core.hpp"

int main() {
    act::Graph G;
    
    // Создаем одну пробную вершину (хронон)
    act::Vertex v1;
    v1.id = 0;
    v1.octant = 1;
    
    G.vertices.push_back(v1);

    std::cout << "ACT Engine Initialized!" << std::endl;
    std::cout << "Vertices in graph: " << G.vertices.size() << std::endl;
    
    return 0;
}



# 1. Компилируем наш код в исполняемый файл 'act_engine'
!g++ main.cpp -o act_engine

# 2. Запускаем скомпилированную программу
!./act_engine



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

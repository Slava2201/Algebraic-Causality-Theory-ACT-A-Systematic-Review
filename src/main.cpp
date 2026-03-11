%%writefile main.cpp
#include <iostream>
#include "act_core.hpp"
#include "physics.hpp"
#include "generator.hpp"
#include "simulation.hpp" // Теперь подключаем новый файл!

int main() {
    act::Graph G;
    act::generate_simple_cell(G);

    std::cout << "\n--- Starting Monte Carlo Simulation ---" << std::endl;
    
    double beta = 2.0; // "Обратная температура" симуляции
    int steps = 10000;

    // Запускаем цикл симуляции
    for(int i = 0; i < steps; ++i) {
        act::metropolis_step(G, beta);
        
        // Каждые 2500 шагов выводим промежуточный результат
        if (i % 2500 == 0) {
            double total_density = 0;
            for(const auto& v : G.vertices) {
                total_density += act::estimate_psi_density(v);
            }
            std::cout << "Step " << i << ": Total system density = " << total_density << std::endl;
        }
    }

    std::cout << "--- Simulation Finished ---" << std::endl;
    
    // Финальный замер в вершине 0
    double final_d0 = act::estimate_psi_density(G.vertices[0]);
    std::cout << "Final density at Vertex 0: " << final_d0 << std::endl;

    return 0;
}

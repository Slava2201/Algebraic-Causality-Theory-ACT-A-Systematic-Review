#ifndef ACT_CORE_HPP
#define ACT_CORE_HPP

#include <vector>
#include <complex>
#include <Eigen/Dense>

namespace act {

using Complex = std::complex<double>;
using Matrix44 = Eigen::Matrix<Complex, 4, 4>;
using Matrix3x3SU = Eigen::Matrix<Complex, 3, 3>;

/**
 * @brief Vertex represents a chronon in the ACT network.
 */
struct Vertex {
    int id;
    int octant;                 // 0-7, defines local geometry
    Complex tau[32];            // chronon state (spinor-like)
    Complex psi[4];              // fermion field value
    std::vector<int> tetrahedra; // indices of incident tetrahedra
};

/**
 * @brief Edge represents a causal link between two chronons.
 */
struct Edge {
    int id;
    int v1, v2;
    Matrix3x3SU U;              // Gauge link (SU(3) x SU(2) x U(1))
};

/**
 * @brief Tetrahedron represents the 4D simplicial volume element.
 */
struct Tetrahedron {
    int id;
    int vertices[4];            // indices of 4 vertices
    double W;                   // tetrahedral invariant value
};

/**
 * @brief Global Graph representing the ACT network configuration.
 */
struct Graph {
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::vector<Tetrahedron> tetrahedra;
};

} // namespace act

#endif // ACT_CORE_HPP

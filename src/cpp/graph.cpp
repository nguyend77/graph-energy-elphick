#include "graph.hpp"
#include <Eigen/Dense>
#include <string>
#include <cmath>
#include <fstream>

Graph fromGRAPH6(const std::string &line) {
    const unsigned int vertices = static_cast<unsigned int>(line[0] - 63);
    const unsigned int bits = vertices*(vertices-1)/2;
    std::string name(bits, '0');
    unsigned int edges = 0;
    unsigned int k = 0;
    for (std::size_t c = 1; c < line.size(); ++c) {
        const unsigned int value = static_cast<unsigned int>(line[c] - 63);
        int b = 5;
        while (b >= 0 && k < bits) {
            if ((value >> b) & 1U) {
                name[k] = '1';
                ++edges;
            }
            --b;
            ++k;
        }
    }
    Eigen::MatrixXd adjacency = Eigen::MatrixXd::Zero(vertices, vertices);
    for (unsigned int i = 1; i < vertices; ++i) {
        for (unsigned int j = 0; j < i; ++j) {
            if (name[i*(i-1)/2 + j] == '1') {
                adjacency(i, j) = 1.0;
                adjacency(j, i) = 1.0;
            }
        }
    }
    return Graph{adjacency, vertices, edges, name};
}

std::string printMatrix(const Graph &g) {
    const unsigned int n = g.vertices;
    std::string matrix(n * 2 * n, ' ');
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            matrix[(i*n + j) * 2] = g.adjacency(i, j) != 0.0 ? '1' : '0';
        }
        matrix[(i*n + n - 1) * 2 + 1] = '\n';
    }
    return matrix;
}

Spectrum getSpectrum(const Graph &g) {
    const unsigned int n = g.vertices;
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(g.adjacency, Eigen::EigenvaluesOnly);
    const Eigen::VectorXd eigenvalues = solver.eigenvalues();
    Spectrum s {eigenvalues(n-1), 0.0};
    for (unsigned int i = 0; i < n; ++i) { s.energy += std::abs(eigenvalues(i)); }
    return s;
}

bool passUpperBound(const Graph &g) {
    const Spectrum s = getSpectrum(g);
    const double upperBound = 2.0 * g.edges / std::sqrt(s.radius);
    return s.energy <= upperBound + EPSILON;
}

void searchCounterexample(const unsigned int &n) {
    const std::string suffix = std::to_string(n) + "vertices.txt";
    std::ifstream inFile("../../data/input/" + suffix);
    std::ofstream outFile("../../data/output/" + suffix);
    outFile << "Results for graphs with " << n << " vertices.\n\n";
    std::string line;
    unsigned int tested = 0;
    unsigned int failed = 0;
    while (std::getline(inFile, line)) {
        if (line.empty()) { continue; }
        const Graph g = fromGRAPH6(line);
        ++tested;
        if (!passUpperBound(g)) {
            outFile << g.name << "\n---\n" << printMatrix(g) << '\n';
            ++failed;
        }
    }
    outFile << "Tested " << tested << " graphs and found " << failed << " counterexamples.\n";
    outFile.close();
}

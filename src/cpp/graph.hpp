#ifndef GRAPH_H
#define GRAPH_H

#include <Eigen/Dense>
#include <string>

struct Graph {
    Eigen::MatrixXd adjacency;
    unsigned int vertices;
    unsigned int edges;
    std::string name;
};

struct Spectrum {
    double radius;
    double energy;
};

inline constexpr double EPSILON = 1e-9;

Graph fromGRAPH6(const std::string &line);

std::string printMatrix(const Graph &g);

Spectrum getSpectrum(const Graph &g);

bool passUpperBound(const Graph &g);

void searchCounterexample(const unsigned int &n);

#endif

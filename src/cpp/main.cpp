#include "graph.hpp"

int main() {
    const unsigned int target = 11;
    for (unsigned int n = 2; n <= target; ++n) { searchCounterexample(n); }
    return 0;
}

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

bool has_arbitrage_opportunity(const std::vector<std::vector<double>>& exchange_rates) {
    int n = exchange_rates.size();
    std::vector<double> distances(n, std::numeric_limits<double>::max());
    distances[0] = 0;

    /*
        Firstly, we note that Bellman-Ford computes the path weight by adding the individual
        edge weights. To make this work for exchange rates, which are multiplicative, an elegant 
        fix is to first take the logs of all the edge weights. Thus when we sum edge weights along a 
        path we are actually multiplying exchange rates – we can recover the multiplied quantity 
        by exponentiating the sum. Secondly, Bellman-Ford attempts to find minimum weight paths and 
        negative edge cycles, whereas our arbitrage problem is about maximising the amount of currency 
        received. Thus as a simple modification, we must also make our log weights negative.
        
        log(a+b) = log(a) * log(b)
    */

    // Transform exchange rates to their logarithms and negate them
    std::vector<std::vector<double>> log_exchange_rates(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            log_exchange_rates[i][j] = -log(exchange_rates[i][j]);
        }
    }
    
    /*
        This line of code is the core part of the Bellman-Ford 
        algorithm, which is used to relax the edges of the graph. The purpose of this relaxation step
        is to update the tentative shortest path distances between vertices.

        distances[j] represents the current shortest path distance from the source vertex to vertex j. 
        The expression distances[i] + log_exchange_rates[i][j] calculates the new tentative distance from the
        source vertex to vertex j by going through vertex i. If this new tentative distance is shorter 
        than the current distance (distances[j]), the algorithm updates distances[j] with the new value.
        
        By iteratively relaxing all the edges in the graph, the Bellman-Ford algorithm computes the shortest path
        distances from the source vertex to all other vertices. If a negative weight cycle is present, the algorithm
        can detect it, which indicates an arbitrage opportunity in the context of the problem.
    */

    // Apply the Bellman-Ford algorithm
    for (int k = 0; k < n - 1; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                distances[j] = std::min(distances[j], distances[i] + log_exchange_rates[i][j]);
            }
        }
    }
    
    /*
        This line of code is used to check if the current tentative distance to 
        vertex j can be improved by going through vertex i. If the current distance distances[j] 
        is greater than the distance from the source vertex to vertex i (distances[i]) plus the edge 
        weight between vertices i and j (log_exchange_rates[i][j]), it means there 
        is a shorter path through vertex i.
    
        In the context of the Bellman-Ford algorithm, this condition is checked after iterating 
        through all vertices and relaxing their edges. If this condition is still true for any edge (i, j), 
        it implies that there is a negative weight cycle in the graph, because the distances can 
        still be improved even after performing the relaxation step for all vertices.
    */

    // Check for negative cycles
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distances[j] > distances[i] + log_exchange_rates[i][j]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    std::vector<std::vector<double>> exchange_rates = {
        {1, 0.5, 0.5},
        {2, 1, 0.5},
        {2, 2, 1}
    };

    bool has_arbitrage = has_arbitrage_opportunity(exchange_rates);
    std::cout << (has_arbitrage ? "Yes" : "No") << std::endl;

    return 0;
}
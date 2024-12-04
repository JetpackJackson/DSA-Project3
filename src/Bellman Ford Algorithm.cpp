#include <vector>
#include <iostream>
#include <limits>
#include <thread> // For adding sleep to the loading bar (optional)
using namespace std;

// Bellman-Ford algorithm for shortest path from a single source
vector<double> bellman_ford(const vector<vector<double>>& graph, int start) {
    int n = graph.size(); // Number of nodes in the graph
    vector<double> distances(n, numeric_limits<double>::infinity()); // Set all distances to infinity
    distances[start] = 0.0; // Set the distance to the source node as 0
    cout << "Processing:" << endl;

    // Relax edges (n-1) times because the maximum path length is (n-1) edges
    for (int step = 0; step < n - 1; step++) {

        bool any_update = false; // Keep track of whether any distance was updated
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                // Check if there's a valid edge from u to v
                if (graph[u][v] != numeric_limits<double>::infinity()) {
                    double new_distance = distances[u] + graph[u][v]; // Calculate potential new distance
                    if (new_distance < distances[v]) { // Update if the new distance is shorter
                        distances[v] = new_distance;
                        any_update = true; // Mark that we updated at least one distance
                    }
                }
            }
        }

        // Show a loading bar (dots for each step)
        cout << "Processing: ";
        for (int i = 0; i <= step; i++) {
            cout << ".";
        }
        cout << endl;

        // If no distances were updated, stop early
        if (!any_update) {
            cout << "No updates in this iteration. Algorithm finished early." << endl;
            break;
        }
    }

    // Check for negative-weight cycles (a cycle that reduces total distance indefinitely)
    cout << "Checking for negative-weight cycles..." << endl;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != numeric_limits<double>::infinity() &&
                distances[u] + graph[u][v] < distances[v]) {
                cerr << "Error: Graph contains a negative-weight cycle." << endl;
                return {}; // Return an empty vector to indicate failure
            }
        }
    }

    // Algorithm finished successfully
    cout << "Bellman-Ford completed successfully!" << endl;
    return distances; // Return the shortest distances from the source node
}

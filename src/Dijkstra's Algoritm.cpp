#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Load the graph from a file where it's saved as a binary file.
// This helps us avoid rebuilding the graph every time the program runs.
vector<vector<double>> load_graph(const string& filename) {
    ifstream infile(filename, ios::binary);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return {}; // Return an empty graph if the file doesn't open.
    }

    size_t n;
    infile.read((char*)&n, sizeof(n)); // Read how many nodes are in the graph.
    vector<vector<double>> graph(n, vector<double>(n)); // Create a square adjacency matrix of size n x n.

    // Fill the graph with the weights from the file.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            infile.read((char*)&graph[i][j], sizeof(graph[i][j])); // Read each weight value.
        }
    }

    infile.close();
    cout << "Graph loaded from " << filename << " successfully." << endl;
    return graph; // Return the fully loaded graph.
}

// Implements Dijkstra's Algorithm to find the shortest path from a starting node.
vector<double> dijkstra(const vector<vector<double>>& graph, int start) {
    int n = graph.size();
    vector<double> distances(n, numeric_limits<double>::infinity()); // Initialize all distances to infinity.
    vector<bool> visited(n, false); // Keep track of which nodes have already been processed.
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; // Min-heap for efficient distance updates.

    // Start at the given node with a distance of 0.
    distances[start] = 0.0;
    pq.push(make_pair(0.0, start)); // Add the starting node to the priority queue.

    while (!pq.empty()) {
        int current = pq.top().second; // Get the node with the smallest distance.
        pq.pop();

        // Skip nodes we've already visited.
        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        // Go through all neighbors of the current node.
        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (graph[current][neighbor] != numeric_limits<double>::infinity()) { // Check if there's a valid edge.
                double new_distance = distances[current] + graph[current][neighbor]; // Calculate the new distance.
                if (new_distance < distances[neighbor]) { // If the new distance is shorter, update it.
                    distances[neighbor] = new_distance;
                    pq.push(make_pair(new_distance, neighbor)); // Add the neighbor to the priority queue.
                }
            }
        }
    }

    return distances; // Return the shortest distances from the starting node.
}

// Reads a CSV file and stores its content in a 2D vector of strings.
vector<vector<string>> read_file(ifstream &file) {
    vector<vector<string>> csvdata; // This will hold all the data from the CSV.
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        string cell;

        // Split the current line by commas and add each cell to the row.
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        csvdata.push_back(row); // Add the row to the main data vector.
    }

    file.close(); // Close the file when done.
    return csvdata; // Return the data as a 2D vector.
}

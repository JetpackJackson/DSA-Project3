#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <cctype>
#include <fstream>
using namespace std;

// Checks if a string is numeric (handles numbers with decimals or negatives).
// This is helpful since some data might be missing or have invalid entries.
bool is_numeric(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c) && c != '.' && c != '-') {
            return false; // Return false if any character is not a digit, decimal, or negative sign.
        }
    }
    return true; // Return true if all characters are valid.
}

// Calculates the "emotional similarity" between two songs based on their features.
// It uses sadness, danceability, and energy to compute the difference as a distance.
double calculate_weight(const vector<string>& song1, const vector<string>& song2) {
    double sadness1 = 0.0, sadness2 = 0.0;
    double danceability1 = 0.0, danceability2 = 0.0;
    double energy1 = 0.0, energy2 = 0.0;

    // Convert string values to doubles if they are numeric, otherwise use 0.0
    if (is_numeric(song1[28])) sadness1 = stod(song1[28]);
    if (is_numeric(song2[28])) sadness2 = stod(song2[28]);
    if (is_numeric(song1[29])) danceability1 = stod(song1[29]);
    if (is_numeric(song2[29])) danceability2 = stod(song2[29]);
    if (is_numeric(song1[30])) energy1 = stod(song1[30]);
    if (is_numeric(song2[30])) energy2 = stod(song2[30]);

    // Compute the differences for each feature
    double sadness_diff = sadness1 - sadness2;
    double danceability_diff = danceability1 - danceability2;
    double energy_diff = energy1 - energy2;

    // Return the Euclidean distance as the "weight" between the two songs
    return sqrt((sadness_diff * sadness_diff) +
                (danceability_diff * danceability_diff) +
                (energy_diff * energy_diff));
}

// Builds a graph (as an adjacency matrix) where each song is a node,
// and the edges represent emotional similarity between songs.
vector<vector<double>> build_graph(const vector<vector<string>>& csvdata) {
    size_t n = csvdata.size();
    vector<vector<double>> graph(n, vector<double>(n, numeric_limits<double>::infinity())); // Start with all distances as infinity.

    cout << "Building graph with " << n << " nodes..." << endl;

    // Calculate weights between each pair of songs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) { // Skip self-loops (no edge from a song to itself).
                graph[i][j] = calculate_weight(csvdata[i], csvdata[j]);
            }
        }
        // Show progress every 1000 nodes so we know it's working.
        if (i % 1000 == 0) {
            cout << "Processed " << i << " / " << n << " nodes..." << endl;
        }
    }

    cout << "Graph construction complete!" << endl;
    return graph;
}

// Saves the graph (adjacency matrix) to a binary file so it can be reloaded later.
// This avoids having to rebuild the graph every time the program is run.
void save_graph(const vector<vector<double>>& graph, const string& filename) {
    ofstream outfile(filename, ios::binary);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return; // Exit the function if the file couldn't be opened.
    }

    size_t n = graph.size();
    outfile.write((char*)&n, sizeof(n)); // Write the number of nodes first.

    // Write each row of the adjacency matrix to the file.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile.write((char*)&graph[i][j], sizeof(graph[i][j])); // Write each edge weight.
        }
    }

    outfile.close(); // Always close the file.
    cout << "Graph saved to " << filename << " successfully." << endl;
}

// returns an integer corresponding to index in 2-D array if song is found in csvdata, returns -1 if not found
int search_string (const std::string& song_name, const std::vector<std::vector<std::string>>& csvdata) {
    for (int i = 0; i < csvdata.size(); i++) {
        if (csvdata[i][2] == song_name) return i;
    }
    return -1;
}

string process_string(const std::string& song) {
    string new_song;
    for (auto& c: song) {
        if (isalpha(c)) new_song += tolower(c);
        else new_song += c;
    }
    return new_song;
}


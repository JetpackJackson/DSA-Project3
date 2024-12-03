#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include <fstream>

// Checks if a string is numeric (e.g., it can be converted to a number).
// This is useful for validating the dataset before performing calculations.
bool is_numeric(const std::string& str);

// Calculates the "weight" or "emotional similarity" between two songs.
// This is based on their sadness, danceability, and energy attributes.
double calculate_weight(const std::vector<std::string>& song1, const std::vector<std::string>& song2);

// Builds a graph (represented as an adjacency matrix) from the song dataset.
// Each song is a node, and edges represent the similarity between songs.
std::vector<std::vector<double>> build_graph(const std::vector<std::vector<std::string>>& csvdata);

// Saves the graph (adjacency matrix) to a file in binary format.
// This allows us to reuse the graph without rebuilding it each time.
void save_graph(const std::vector<std::vector<double>>& graph, const std::string& filename);

// Loads the graph from a binary file. This is useful if the graph was saved earlier,
// so we don't have to reconstruct it from the dataset again.
std::vector<std::vector<double>> load_graph(const std::string& filename);

// Runs Dijkstra's Algorithm to find the shortest path from a given start node
// to all other nodes in the graph. Useful for calculating emotional paths between songs.
std::vector<double> dijkstra(const std::vector<std::vector<double>>& graph, int start);

// Reads a CSV file and loads its contents into a 2D vector of strings.
// Each row in the CSV becomes a vector, with cells as individual strings.
std::vector<std::vector<std::string>> read_file(std::ifstream& file, std::vector<std::vector<std::string>> csvdata);

#endif // ALGORITHM_H

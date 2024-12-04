#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Algorithm.h"
using namespace std;

// Function to read the CSV file into a 2D vector of strings.
// Each row of the CSV becomes a vector of strings (representing the columns).
vector<vector<string>> read_file(ifstream &file, vector<vector<string>> csvdata) {
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        // Split each line by commas and add the values to the 'row' vector.
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        // Add the row to our main 'csvdata' vector.
        csvdata.push_back(row);
    }
    file.close(); // Always close the file when you're done with it.
    return csvdata;
}

int main(int argc, char *argv[]) {
    vector<vector<double>> graph;
    vector<vector<string>> csvdata;
    string graphFile = "graph.dat";

    // Check if the graph file exists
    ifstream graphCheck(graphFile);
    if (graphCheck.is_open()) {
        // If the graph file exists, load the graph from the binary file.
        cout << "Graph file found. Loading graph from " << graphFile << "..." << endl;
        graph = load_graph(graphFile);
        graphCheck.close();

        // Load the CSV data for song details (to print names, artists, etc.).
        ifstream file("data.csv");
        if (!file.is_open()) {
            cerr << "Error opening CSV file. Ensure it exists in the correct location." << endl;
            return 1; // Exit the program if the file isn't found.
        }
        csvdata = read_file(file, {});
    } else {
        // If the graph file does not exist, build the graph from the CSV file.
        cout << "Graph file not found. Building the graph from the dataset..." << endl;

        // Let's start by opening the CSV file.
        cout << "Looking for file at: data.csv" << endl;
        ifstream file("data.csv");
        if (!file.is_open()) {
            cerr << "Error opening file. Ensure it exists in the correct location." << endl;
            return 1; // Exit the program if the file isn't found.
        }

        // Read the file and store its contents in a 2D vector.
        csvdata = read_file(file, {});

        // Build the graph based on the dataset (this will calculate weights between songs).
        graph = build_graph(csvdata);

        // Save the graph to a file so we don't have to rebuild it every time.
        save_graph(graph, graphFile);
        cout << "Graph built and saved successfully!" << endl;
    }

    // Randomly pick two songs from the dataset for testing.
    srand(time(0)); // Seed the random number generator with the current time.
    int song1 = rand() % csvdata.size();
    int song2 = rand() % csvdata.size();

    // Print the details of the two randomly chosen songs.
    cout << "Song 1: " << csvdata[song1][2] << " by " << csvdata[song1][1] << endl;
    cout << "  Sadness: " << csvdata[song1][28] << ", Danceability: " << csvdata[song1][29]
         << ", Energy: " << csvdata[song1][30] << endl;

    cout << "Song 2: " << csvdata[song2][2] << " by " << csvdata[song2][1] << endl;
    cout << "  Sadness: " << csvdata[song2][28] << ", Danceability: " << csvdata[song2][29]
         << ", Energy: " << csvdata[song2][30] << endl;

    // Loop to allow the user to select an algorithm repeatedly
    string choice = "";
    while (true) {
        cout << "\nWhich algorithm would you like to use? [type 'd' for Dijkstra's, 'f' for Bellman-Ford, or 'q' to quit]:\n";
        cin >> choice;

        if (choice == "d") {
            // Run Dijkstra's Algorithm to find the shortest path from one song to the other.
            cout << "Running Dijkstra's Algorithm..." << endl;
            vector<double> distances = dijkstra(graph, song1);
            cout << "Shortest emotional path from Song 1 to Song 2: " << distances[song2] << endl;

        } else if (choice == "f") {
            // Run Bellman-Ford Algorithm
            cout << "Running Bellman-Ford Algorithm..." << endl;
            vector<double> distances = bellman_ford(graph, song1);
            if (!distances.empty()) {
                cout << "Shortest emotional path from Song 1 to Song 2: " << distances[song2] << endl;
            } else {
                cout << "Bellman-Ford failed due to a negative-weight cycle." << endl;
            }
        } else if (choice == "q") {
            // Exit the loop and program
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else {
            // Invalid input, prompt again
            cout << "Invalid choice. Please type 'd', 'f', or 'q'." << endl;
        }
    }

    return 0;
}

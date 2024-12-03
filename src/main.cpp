#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Algorithm.h"
using namespace std;

// This function reads the CSV file and splits its contents into a 2D vector of strings.
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
    // Let's start by opening the CSV file.
    cout << "Looking for file at: data.csv" << endl;
    ifstream file("data.csv");
    if (!file.is_open()) {
        cerr << "Error opening file. Ensure it exists in the correct location." << endl;
        return 1; // Exit the program if the file isn't found.
    }

    // Read the file and store its contents in a 2D vector.
    vector<vector<string>> csvdata = read_file(file, {});

    // Randomly pick two songs from the dataset.
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

    // Build the graph based on the dataset (this will calculate weights between songs).
    cout << "Building the graph..." << endl;
    vector<vector<double>> graph = build_graph(csvdata);

    //Save the graph to a file so we don't have to rebuild it every time.
    save_graph(graph, "graph.dat");
    cout << "Graph built successfully!" << endl;

    // Ask the user which algorithm they want to use (Dijkstra or Floyd-Warshall).
    string choice = "";
    while (choice != "d" && choice != "f") {
        cout << "Which algorithm to use? [type 'd' for Dijkstra's or 'f' for Floyd-Warshall] \n";
        cin >> choice;

        if (choice == "d") {
            // Run Dijkstra's Algorithm to find the shortest path from one song to the other.
            cout << "Running Dijkstra's Algorithm..." << endl;
            vector<double> distances = dijkstra(graph, song1);
            cout << "Shortest emotional path from Song 1 to Song 2: " << distances[song2] << endl;

        } else if (choice == "f") {
            // This is a placeholder for Floyd-Warshall (not implemented yet).
            cout << "Running Floyd-Warshall Algorithm..." << endl;
            cout << "Floyd-Warshall is not implemented yet!" << endl;

        } else {
            // If the user enters anything other than 'd' or 'f', prompt them again.
            cout << "Please type 'd' or 'f'." << endl;
        }
    }

    return 0;
}

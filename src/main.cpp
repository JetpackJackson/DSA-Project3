#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<string>> read_file(ifstream &file,
                                 vector<vector<string>> csvdata) {
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    string cell;
    vector<string> row;

    // split
    while (getline(ss, cell, ',')) {
      row.push_back(cell);
    }
    // add to vec
    csvdata.push_back(row);
  }
  file.close();
  return csvdata;
}

int main(int argc, char *argv[]) {
  string choice = "";
  cout << "Would you like to pick two random songs to compare? [y/n] ";
  cin >> choice;

  if (choice == "y") {
    // get data
    ifstream file("data.csv");
    if (!file.is_open()) {
      cerr << "Error opening file" << endl;
      return 1;
    }
    vector<vector<string>> csvdata;
    csvdata = read_file(file, csvdata);

    // do stuff
    choice = "";
    while (choice != "d" && choice != "f") {
      cout << "Which algorithm to use? [type 'd' for Dijkstra's or 'f' for "
              "Floyd-Warshall] ";
      cin >> choice;
      if (choice == "d") {
        // TODO: dijkstra
      } else if (choice == "f") {
        // TODO: floyd
      } else {
        cout << "Please type 'd' or 'f'." << endl;
      }
    }

  } else {
    cout << "Alright, have a good day!" << endl;
    return 0;
  }

  // output all data
  // for (const auto &row : csvdata) {
  //   for (const auto &cell : row) {
  //     cout << cell << " ";
  //   }
  //   cout << endl;
  // }

  return 0;
}

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

int main() {
  map<char, vector<pair<int, int>>> antennas;
  int row, col = 0;
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    col = 0;
    for (char c : line) {
      if (c != '.') {
        if (antennas.find(c) == antennas.end()) {
          antennas[c] = vector<pair<int, int>>();
        }
        antennas[c].push_back(make_pair(col, row));
      }
      ++col;
    }
    ++row;
  }

  set<pair<int, int>> antinode_locations;
  set<pair<int, int>> updated_antinode_locations;

  for (auto [frequency, locations] : antennas) {
    for (int i = 0; i < locations.size(); i++) {
      for (int j = i + 1; j < locations.size(); j++) {
        int x_diff = locations[i].first - locations[j].first;
        int y_diff = locations[i].second - locations[j].second;
        int diff_multiplier = 0;

        while (locations[i].first + (x_diff * diff_multiplier) >= 0 && locations[i].first + (x_diff * diff_multiplier) < col && locations[i].second + (y_diff * diff_multiplier) >= 0 && locations[i].second + (y_diff * diff_multiplier) < col) {
          if (diff_multiplier == 1) {
            antinode_locations.insert(make_pair(locations[i].first + x_diff, locations[i].second + y_diff));
          }
          updated_antinode_locations.insert(make_pair(locations[i].first + (x_diff * diff_multiplier), locations[i].second + (y_diff * diff_multiplier)));
          ++diff_multiplier;
        }

        diff_multiplier = 0;
        while (locations[j].first - (x_diff * diff_multiplier) >= 0 && locations[j].first - (x_diff * diff_multiplier) < col && locations[j].second - (y_diff * diff_multiplier) >= 0 && locations[j].second - (y_diff * diff_multiplier) < col) {
          if (diff_multiplier == 1) {
            antinode_locations.insert(make_pair(locations[j].first - x_diff, locations[j].second - y_diff));
          }
          updated_antinode_locations.insert(make_pair(locations[j].first - (x_diff * diff_multiplier), locations[j].second - (y_diff * diff_multiplier)));
          ++diff_multiplier;
        }
      }
    }
  }

  cout << antinode_locations.size() << " " << updated_antinode_locations.size() << endl;
  return 0;
}

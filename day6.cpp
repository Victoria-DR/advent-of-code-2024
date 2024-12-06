#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int find_distinct_positions(vector<vector<char>> &data, int guard_x, int guard_y, char guard_direction) {
  int distinct_positions = 1;
  map<string, vector<char>> encountered_obstacles;

  while (1) {
    if (guard_y < 0 || guard_y >= data.size() || guard_x < 0 || guard_x >= data[0].size()) {
      break;
    }

    if (data[guard_y][guard_x] == '.') {
      data[guard_y][guard_x] = 'X';
      ++distinct_positions;
    } else if (data[guard_y][guard_x] == '#' || data[guard_y][guard_x] == '$') {
      if (data[guard_y][guard_x] == '#') {
        data[guard_y][guard_x] = '$';
        encountered_obstacles[to_string(guard_x) + "," + to_string(guard_y)] = vector<char>(1, guard_direction);
      } else {
        if (find(encountered_obstacles[to_string(guard_x) + "," + to_string(guard_y)].begin(), encountered_obstacles[to_string(guard_x) + "," + to_string(guard_y)].end(), guard_direction) == encountered_obstacles[to_string(guard_x) + "," + to_string(guard_y)].end()) {
          encountered_obstacles[to_string(guard_x) + "," + to_string(guard_y)].push_back(guard_direction);
        } else {
          return -1;
        }
      }

      switch (guard_direction) {
        case '^':
          ++guard_y;
          guard_direction = '>';
          break;
        case 'v':
          --guard_y;
          guard_direction = '<';
          break;
        case '<':
          ++guard_x;
          guard_direction = '^';
          break;
        case '>':
          --guard_x;
          guard_direction = 'v';
          break;
      }
    }

    switch (guard_direction) {
      case '^':
        --guard_y;
        break;
      case 'v':
        ++guard_y;
        break;
      case '<':
        --guard_x;
        break;
      case '>':
        ++guard_x;
        break;
    }
  }

  return distinct_positions;
}

int find_obstruction_positions(vector<vector<char>> &data, int guard_x, int guard_y, char guard_direction) {
  int obstruction_positions = 0;
  
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[0].size(); j++) {
      if (data[i][j] == '.') {
        vector<vector<char>> data_with_obstruction = data;
        data_with_obstruction[i][j] = '#';
        if (find_distinct_positions(data_with_obstruction, guard_x, guard_y, guard_direction) == -1) {
          ++obstruction_positions;
        }
      }
    }
  }

  return obstruction_positions;
}

int main() {
  int guard_x, guard_y;
  char guard_direction;

  vector<vector<char>> data{};
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    data.push_back(vector<char>{});
    for (char c : line) {
      data.back().push_back(c);
      if (c == '^' || c == 'v' || c == '<' || c == '>') {
        guard_x = data.back().size() - 1;
        guard_y = data.size() - 1;
        guard_direction = c;
      }
    }
  }

  vector<vector<char>> data_copy = data;
  cout << find_distinct_positions(data_copy, guard_x, guard_y, guard_direction) << " ";
  cout << find_obstruction_positions(data, guard_x, guard_y, guard_direction) << endl;
  return 0;
}

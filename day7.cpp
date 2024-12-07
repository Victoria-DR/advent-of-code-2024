#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

long apply_operation(long num1, int num2, char op) {
  switch (op) {
    case '+':
      return num1 + num2;
    case '*':
      return num1 * num2;
    case '|':
      return stol(to_string(num1) + to_string(num2));
    default:
      return 0;
  }
}

int main() {
  map<long, vector<int>> data{};
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    int colon_index = line.find(":");
    if (data.count(stol(line.substr(0, colon_index)))) {
      cout << "Duplicate calibration found: " << line << endl;
      continue;
    }
    data[stol(line.substr(0, colon_index))] = vector<int>();
    int num_index = colon_index + 2;
    int space_index = line.find(" ", num_index);
    while (space_index != string::npos) {
      data[stol(line.substr(0, colon_index))].push_back(stoi(line.substr(num_index, space_index - num_index)));
      num_index = space_index + 1;
      space_index = line.find(" ", num_index);
    }
    data[stol(line.substr(0, colon_index))].push_back(stoi(line.substr(num_index)));
  }

  long total_calibration = 0;

  for (auto &pair : data) {
    for (int multipliers = 0; multipliers < pair.second.size(); multipliers++) {
      string operators(multipliers, '*');
      operators.append(pair.second.size() - 1 - multipliers, '+');

      bool done = false;
      do {
        long result = (long) pair.second[0];
        for (int i = 1; i < pair.second.size(); i++) {
          result = apply_operation(result, pair.second[i], operators[i - 1]);
        }
        if (result == pair.first) {
          total_calibration += pair.first;
          done = true;
          break;
        }
      } while (next_permutation(operators.begin(), operators.end()));

      if (done) {
        break;
      }
    }
  }

  cout << total_calibration << endl;

  long new_total_calibration = 0;

  for (auto &pair : data) {
    for (int multipliers = 0; multipliers < pair.second.size(); multipliers++) {
      string multis(multipliers, '*');
      bool done = false;
      for (int adders = 0; adders < pair.second.size() - multipliers; adders++) {
        string operators(multis);
        operators.append(adders, '+');
        operators.append(pair.second.size() - 1 - multipliers - adders, '|');
        
        do {
          long result = (long) pair.second[0];
          for (int i = 1; i < pair.second.size(); i++) {
            result = apply_operation(result, pair.second[i], operators[i - 1]);
          }
          if (result == pair.first) {
            new_total_calibration += pair.first;
            done = true;
            break;
          }
        } while (next_permutation(operators.begin(), operators.end()));

        if (done) {
          break;
        }      
      }

      if (done) {
        break;
      }
    }
  }

  cout << new_total_calibration << endl;

  return 0;
}

// Run again against duplicate keys.

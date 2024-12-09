#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

long partOne(string line) {
  long checksum = 0;
  int disk_index = 0;
  int file_block = 0;
  int last_file_index = line.size() - 1;
  int last_file_remaining = stoi(line.substr(line.size() - 1, 1));

  while (1) {
    if (disk_index >= line.size()) {
      break;
    } else if (disk_index >= last_file_index) {
      for (int i = 0; i < last_file_remaining; i++) {
        checksum += last_file_index / 2 * file_block;
        ++file_block;
      }
      break;
    }

    if (disk_index % 2 == 0) {
      for (int i = 0; i < stoi(line.substr(disk_index, 1)); i++) {
        checksum += (disk_index / 2) * file_block;
        ++file_block;
      }
    } else {
      for (int i = 0; i < stoi(line.substr(disk_index, 1)); i++) {
        if (last_file_remaining == 0) {
          last_file_index -= 2;
          last_file_remaining = stoi(line.substr(last_file_index, 1));
        }
        checksum += (last_file_index / 2) * file_block;
        ++file_block;
        --last_file_remaining;
      }
    }

    ++disk_index;
  }

  return checksum;
}

long partTwo(string line) {
  vector<pair<int, int>> file_sizes;
  for (int i = 0; i < line.size(); i += 2) {
    int size = stoi(line.substr(i, 1));
    file_sizes.push_back(make_pair(i / 2, size));
  }

  vector<int> disk_map;
  vector<int> moved_files;
  for (int i = 0; i < line.size(); i++) {
    int size = stoi(line.substr(i, 1));
    if (i % 2 == 0) {
      if (find(moved_files.begin(), moved_files.end(), i / 2) == moved_files.end()) {
        for (int j = 0; j < size; j++) {
          disk_map.push_back(i / 2);
        }
        file_sizes.erase(file_sizes.begin());
        continue;
      }
    }

    int reverse_index = file_sizes.size() - 1;
    while (size > 0 && reverse_index >= 0) {
      if (file_sizes[reverse_index].second <= size) {
        for (int j = 0; j < file_sizes[reverse_index].second; j++) {
          disk_map.push_back(file_sizes[reverse_index].first);
        }
        size -= file_sizes[reverse_index].second;
        moved_files.push_back(file_sizes[reverse_index].first);
        file_sizes.erase(file_sizes.begin() + reverse_index);
      }
      --reverse_index;
    }

    for (int j = 0; j < size; j++) {
      disk_map.push_back(0);
    }
  }

  long checksum = 0;
  for (int i = 0; i < disk_map.size(); i++) {
    checksum += disk_map[i] * i;
  }

  return checksum;
}

int main() {
  ifstream file("input.txt");
  string line;
  getline(file, line);
  
  cout << partOne(line) << " " << partTwo(line) << endl;
  return 0;
}

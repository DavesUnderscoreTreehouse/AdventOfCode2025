#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  // Filepath for rollMap data
  string filepath = "input.txt";
  // Read from the text file
  ifstream f(filepath);
  
  int accessibleRolls, adjCount, removedRollsCount;
  string removedRollsLine;
  vector<char> v_rollMapLine, v_removedRollsLine;
  vector<vector<char>> rollMap, removedRolls;
  
  // For each line
  while (getline(f, removedRollsLine)) {
    v_removedRollsLine.erase (v_removedRollsLine.begin(), v_removedRollsLine.end());
    for (char c : removedRollsLine) {
      v_removedRollsLine.push_back(c);
    }
    removedRolls.push_back(v_removedRollsLine);
  }
  
  // repeat from here with rolls removed
  removedRollsCount = 0;
  do {
    accessibleRolls = 0;
    // copy modified removedRolls vector into live rollMap vector
    rollMap.erase(rollMap.begin(), rollMap.end());
    for (int i = 0; i < removedRolls.size(); i++) {
      v_rollMapLine.erase(v_rollMapLine.begin(), v_rollMapLine.end());
      for (int j = 0; j < removedRolls[i].size(); j++) {
        v_rollMapLine.push_back(removedRolls.at(i).at(j));
      }
      rollMap.push_back(v_rollMapLine);
    }
    // for each element in live rollMap
    for (int i = 0; i < rollMap.size(); i++) {
      for (int j = 0; j < rollMap[i].size(); j++) {
        // if roll
        if ((rollMap.at(i).at(j) == '@')) {
          adjCount = 0;
          // use try catch
          try {
            // check adjecent
            for (int p = i - 1; p <= (i + 1); p++) {
              for (int q = j - 1; q <= (j + 1); q++) {
                if ((p < rollMap.size()) && (q < rollMap[i].size()) && (rollMap.at(p).at(q) == '@')) {
                  adjCount++;
                }
              }
            }
          } catch (const out_of_range& oor) {
            cerr << "adj check: Out of range error at line " << (i + 1) << ": " << oor.what() << "\n";
          }
          // if less than 4 add to accesible rolls
          if (adjCount <= 4) {
            accessibleRolls++;
            // update removedRolls copy of rollMap with removed roll
            try {
              removedRolls.at(i).at(j) = 'x';
              removedRollsCount++;
            } catch(const out_of_range& oor) {
              cerr << "roll removal: Out of range error at line " << (i + 1) << ": " << oor.what() << "\n";
            }
          }
        }
      }
    }
  } while (accessibleRolls > 0);
  
  
  cout << "\nThe number of rolls removed is: " << removedRollsCount << "\n";

  return 0;
}
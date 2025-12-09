#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

struct Junction {
  int id, x, y, z;
  int connectedId = -1;
  int circuitNo = -1;
  double connectionDist = -1;
};

// Function to compare junctions
bool compareJunctions(Junction a, Junction b)
{
    // If connction distance not the same then
    // returns true for higher total
    if (a.connectionDist != b.connectionDist)
        return a.connectionDist < b.connectionDist;

    return (false);
}

int main() 
{
  int lineCount, closeId;
  double dist, oldDist, xDist, yDist, zDist;
  char comma;
  string filepath, inputText;
  vector<int> circuitSizes;
  
  filepath = "testinput.txt";
  ifstream f(filepath);
  
  lineCount = 0;
  while (getline(f, inputText)) {
    lineCount++;
  }
  
  f.clear();
  f.seekg(0);
  
  Junction junctions[lineCount];
  lineCount = 0;
  while (getline(f, inputText)) {
    Junction junction;
    junction.id = lineCount;
    f >> junction.x >> comma >> junction.y >> comma >> junction.z;
    junctions[lineCount] = junction;
    cout << junction.x << "\t, " << junction.y << "\t, " << junction.z << "\n";
    lineCount++;
  }
  cout << "\n";
  
  // find closest junction to each junction
  oldDist = -1;
  closeId = -1;
  for (int i = 0; i < lineCount; i++) {
    cout << "xDist\t" << "yDist\t" << "zDist\t" << "Dist\n";
    for (int j = 0; j < lineCount; j++) {
      xDist = junctions[i].x - junctions[j].x;
      yDist = junctions[i].y - junctions[j].y;
      zDist = junctions[i].z - junctions[j].z;
      dist = sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2));
      cout << xDist << "\t" << yDist << "\t" << zDist << "\t" << dist << "\n";
      if ((dist == 0) && (j == 0)) {
        oldDist = 100000;
      }
      if ((dist != 0) && ((dist < oldDist) || (j == 0))) {
        oldDist = dist;
        closeId = junctions[j].id;
      }
    }
    junctions[i].connectedId = closeId;
    junctions[i].connectionDist = oldDist;
    cout << "Junction:\n";
    cout << junctions[i].x << "\t" << junctions[i].y << "\t" << junctions[i].z << "\t" << junctions[i].connectionDist << "\n\n";
  }
  
  // sort by distance
  sort(junctions, junctions + lineCount, compareJunctions);
  
  // if junctions in same circuit, ignore
  // else, join
  for (int i = 0; i < ((sizeof(junctions) / sizeof(junctions[0])) - 1); i++) {
    // find connected junc obj
    if (junctions[i].connectedId == -1) {
      continue;
    } 
    int j;
    for (j = 0; j < ((sizeof(junctions) / sizeof(junctions[0])) - 1); j++) {
      if (junctions[i].connectedId == junctions[j].id) {
        cout << "Circuit match found: " << junctions[i].id << " connected to " << junctions[j].id << "\n";
        break;
      }
    }
    if ((junctions[i].circuitNo == -1) && (junctions[j].circuitNo == -1)) {
      // circuit tags starting at 1
      junctions[i].circuitNo = circuitSizes.size();
      circuitSizes.push_back(1);
      cout << "New circuit created: " << junctions[i].circuitNo << " size " << circuitSizes.back() << "\n";
    }
    else if (junctions[i].circuitNo == -1) {
      junctions[i].circuitNo = junctions[j].circuitNo;
      circuitSizes.at(junctions[j].circuitNo)++;
      cout << "Junction " << junctions[i].id << " added to circuit " << junctions[j].circuitNo << " new size " << circuitSizes.at(junctions[j].circuitNo) << "\n";
    }
    else if (junctions[j].circuitNo == -1) {
      junctions[j].circuitNo = junctions[i].circuitNo;
      circuitSizes.at(junctions[i].circuitNo)++;
      cout << "Junction " << junctions[j].id << " added to circuit " << junctions[i].circuitNo << " new size " << circuitSizes.at(junctions[i].circuitNo) << "\n";
    }
    else if (junctions[i].circuitNo == junctions[j].circuitNo) {
      continue; // ignore
    }
    else {
      // merge circuits
      int oldCircuitNo = junctions[j].circuitNo;
      int newCircuitNo = junctions[i].circuitNo;
      circuitSizes.at(newCircuitNo) += circuitSizes.at(oldCircuitNo);
      circuitSizes.at(oldCircuitNo) = 0;
      cout << "Merging circuits " << oldCircuitNo << " into " << newCircuitNo << " new size " << circuitSizes.at(newCircuitNo) << "\n";
      // update all junctions with old circuit no
      for (int k = 0; k < ((sizeof(junctions) / sizeof(junctions[0])) - 1); k++) {
        if (junctions[k].circuitNo == oldCircuitNo) {
          junctions[k].circuitNo = newCircuitNo;
        }
      }
    }
    cout << "\n";
  }
  // sort
  sort(circuitSizes.begin(), circuitSizes.end(), greater<>());
  
  cout << "Circuit sizes:\n";
  for (int i : circuitSizes) {
    cout << i << "\n";
  }
  
  // multiply 3 largest
  cout << "Total is: " << circuitSizes.at(0) * circuitSizes.at(1) * circuitSizes.at(2) << "\n";
  return 0;
}
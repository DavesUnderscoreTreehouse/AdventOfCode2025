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
  int connections, lineCount, id, closeId, circuitTotal;
  double oldDist, xDist, yDist, zDist;
  char comma;
  string filepath, inputText;
  vector<int> circuitSizes;
  
  connections = 10;
  filepath = "testinput.txt";
  ifstream f(filepath);
  
  lineCount = 0;
  while (getline(f, inputText)) {
    lineCount++;
  }
  cout << "Line count: " <<lineCount << "\n\n";
  
  f.clear();
  f.seekg(0, ios::beg);
  
  Junction junctions[lineCount];
  double dist[lineCount][lineCount];
  lineCount = 0;
  do {
    Junction junction;
    junction.id = lineCount;
    f >> junction.x >> comma >> junction.y >> comma >> junction.z;
    junctions[lineCount] = junction;
    cout << junction.x << "\t, " << junction.y << "\t, " << junction.z << "\n";
    lineCount++;
  } while (f.peek() != EOF);
  cout << "\n";
  
  // find closest junction to each junction
  // oldDist = -1;
  // closeId = -1;
  for (int i = 0; i < lineCount; i++) {
    //cout << "xDist\t" << "yDist\t" << "zDist\t" << "Dist\n";
    for (int j = 0; j < lineCount; j++) {
      // calculate distances
      xDist = junctions[i].x - junctions[j].x;
      yDist = junctions[i].y - junctions[j].y;
      zDist = junctions[i].z - junctions[j].z;
      dist[i][j] = sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2));
      // //cout << xDist << "\t" << yDist << "\t" << zDist << "\t" << dist << "\n";
      // // if new shortest distance, record
      // if ((dist == 0) && (j == 0)) {
      //   oldDist = 100000;
      // }
      // if ((dist != 0) && ((dist < oldDist) || (j == 0))) {
      //   oldDist = dist;
      //   closeId = junctions[j].id;
      // }
    }
    // junctions[i].connectedId = closeId;
    // junctions[i].connectionDist = oldDist;
    // //cout << "Junction:\n";
    // //cout << junctions[i].x << "\t" << junctions[i].y << "\t" << junctions[i].z << "\t" << junctions[i].connectionDist << "\n\n";
  }
  
  // // sort by distance
  // sort(junctions, junctions + lineCount, compareJunctions);

  cout << "ID" << "\t" << "ConnID" << "\t" << "X" << "\t" << "Y" << "\t" << "Z" << "\t" <<  "Dist" << "\n";
  for (Junction j : junctions) 
    cout << j.id << "\t" << j.connectedId << "\t" << j.x << "\t" << j.y << "\t" << j.z << "\t" << j.connectionDist << "\n";
  cout << "\n";

  // if junctions in same circuit, ignore
  // else, join
  id = -1;
  closeId = -1;
  for (int i = 0; i < connections; i++) {
    // find connected junc obj
    // if (junctions[i].connectedId == -1) {
    //   continue;
    // }

    // find shortest unconnected connection
    oldDist = 100000;
    for (int j = 0; j < lineCount; j++) {
      for (int k = 0; k < lineCount; k++) {
        // if new shortest distance, record
        // Avoid self-connections and only consider shortest valid connection between different or unassigned circuits
        if (j != k && dist[j][k] < oldDist &&
            ((junctions[j].circuitNo == -1 && junctions[k].circuitNo == -1) ||
             (junctions[j].circuitNo != junctions[k].circuitNo))) {
          oldDist = dist[j][k];
          id = j;
          closeId = junctions[k].id;
        } else if (j != k && junctions[j].circuitNo == junctions[k].circuitNo && junctions[j].circuitNo != -1) {
          cout << "Junction " << j << "\t@ " << junctions[j].x << ", " << junctions[j].y << ", " << junctions[j].z << "\n";
          cout << "and      " << k << "\t@ " << junctions[k].x << ", " << junctions[k].y << ", " << junctions[k].z << "\n";
          cout << "already in circuit " << junctions[j].circuitNo << "\n\n";
        }
      }
    }
    junctions[id].connectedId = closeId;
    junctions[id].connectionDist = oldDist;

    // connect
    int connId;
    cout << "For junction " << id << "\t@ " << junctions[id].x << ", " << junctions[id].y << ", " << junctions[id].z << "\n";
    // debug output
    for (connId = 0; connId < lineCount; connId++) {
      if (junctions[id].connectedId == junctions[connId].id) {
        cout << "Circuit match found: " << id << " connected to " << junctions[connId].id  << "\t@ " << junctions[connId].x << ", " << junctions[connId].y << ", " << junctions[connId].z << "\n";
        break;
      }
    }
    if ((junctions[id].circuitNo == -1) && (junctions[connId].circuitNo == -1)) {
      // circuit tags starting at 1
      junctions[id].circuitNo = circuitSizes.size();
      circuitSizes.push_back(1);
      cout << "New circuit created: " << junctions[id].circuitNo << " size " << circuitSizes.back() << "\n";
    }
    else if (junctions[id].circuitNo == -1) {
      junctions[id].circuitNo = junctions[connId].circuitNo;
      circuitSizes.at(junctions[connId].circuitNo)++;
      cout << "Junctions " << junctions[id].id << " added to circuit " << junctions[connId].circuitNo << " new size " << circuitSizes.at(junctions[connId].circuitNo) << "\n";
    }
    else if (junctions[connId].circuitNo == -1) {
      junctions[connId].circuitNo = junctions[id].circuitNo;
      circuitSizes.at(junctions[id].circuitNo)++;
      cout << "Junctions " << junctions[connId].id << " added to circuit " << junctions[id].circuitNo << " new size " << circuitSizes.at(junctions[id].circuitNo) << "\n";
    }
    else if (junctions[id].circuitNo == junctions[connId].circuitNo) {
      continue; // ignore
    }
    else {
      //  merger circuitSizes
      int oldCircuitNo = junctions[connId].circuitNo;
      int newCircuitNo = junctions[id].circuitNo;
      circuitSizes.at(newCircuitNo) += circuitSizes.at(oldCircuitNo);
      circuitSizes.at(oldCircuitNo) = 0;
      cout << "Merging circuits " << oldCircuitNo << " into " << newCircuitNo << " new size " << circuitSizes.at(newCircuitNo) << "\n";
      // update all junctions with old circuit no
      for (int k = 0; k < lineCount; k++) {
        if (junctions[k].circuitNo == oldCircuitNo) {
          junctions[k].circuitNo = newCircuitNo;
        }
      }
    }
    cout << "\n";
  }
  // sort
  sort(circuitSizes.begin(), circuitSizes.end(), greater<>());
  
  circuitTotal = 1;
  cout << "Circuit sizes:\n";
  for (int i = 0; i < circuitSizes.size(); i++) {
    if (i < 3)
      circuitTotal *= circuitSizes.at(i);
    cout << circuitSizes.at(i) << "\n";
  }
  
  // multiply 3 largest
  cout << "Total is: " << circuitTotal << "\n";
  return 0;
}
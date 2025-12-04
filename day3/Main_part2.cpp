#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Battery {
  int index, charge;
};
vector<Battery> vBatteries;

bool compareIndex (Battery i, Battery j) {
  return (i.index < j.index);
}

bool compareCharge (Battery i, Battery j) {
  return (i.charge > j.charge);
}

bool compareGrouped (Battery i, Battery j) {
  if(i.charge != j.charge)
      return (i.charge > j.charge);
  if(i.index != j.index)
      return (i.index > j.index);
  return false;
}

int main() {
  // Filepath for input data
  string filepath = "input.txt";
  // Read from the text file
  ifstream f(filepath);
  
  int64_t joltage = 0;
  int vBatteriesLen, i, j;
  string inputText, concat;
  
  // For each line
  while (getline(f, inputText)) {
    cout << "Input: " << inputText << "\n";
    // Clear previous line
    vBatteries.erase (vBatteries.begin(), vBatteries.end());
    // Load line into int array
    for (i = 0; i < inputText.length(); i++) {
      if (isdigit(inputText[i])) {
        char c = inputText[i];
        struct Battery b = {i, (c- '0')};
        vBatteries.push_back(b);
      }
    }
    
    cout << "vBatteries size pre-pop:  " << vBatteries.size() << "\n";
    
    // sort batteries by indexes grouped by charges
    sort (vBatteries.begin(), vBatteries.end(), compareGrouped);
    
    // extract first 12 elements (12 largest)
    vBatteriesLen = vBatteries.size();
    for (i = 12; i < vBatteriesLen; i++) {
      vBatteries.pop_back();
    }
    
    cout << "vBatteries size post-pop: " << vBatteries.size() << "\n";
    
    //cout << "Indexes sorted by index grouped by charges\n";
    //cout << "index\t| charge\n";
    //for (i = 0; i < vBatteries.size(); i++) {
    //  cout << vBatteries.at(i).index << "\t| " << vBatteries.at(i).charge << "\n";
    //}
    
    // sort values based on indexes
    sort (vBatteries.begin(), vBatteries.end(), compareIndex);
    
    // concatinate
    concat = "";
    for (i = 0; i < vBatteries.size(); i++) {
    	struct Battery b = vBatteries.at(i);
    	concat  = concat + to_string(b.charge);
    }
    
    // sum
    joltage += stoll(concat);
    cout << "Row joltage: " << concat << "\n";
    cout << "\n";
  }
  
  cout << "Final joltage is: " << joltage;

  return 0;
}
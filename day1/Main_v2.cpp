#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int main() 
{
  // Filepath for input data
  string filepath = "input.txt";
  // Dial starting location
  int dialLoc = 50;
  
  // Read from the text file
  ifstream MyReadFile(filepath);
  // Count lines in file
  auto lineCount = std::count_if(std::istreambuf_iterator<char>{MyReadFile}, {}, [](char c) { return c == '\n'; });
  lineCount++;
  // Reset file pointer to beginning
  MyReadFile.seekg(ios::beg);
  // Count zero positions
  int zeroCounter = 0;
  // string array to hold inputs
  string inputs[lineCount];
  // Create a text string, which is used to output the text file
  string inputText;
  
  // Going line by line, calculate dial turns and number of times passing zero
  for (int i = 0; i < lineCount ; i++) {
    getline (MyReadFile, inputText);
    inputs[i] = inputText;
    
    // Extract direction letter
    char direction = inputs[i][0];
    // Extract turns value
    string turns;
    if (sizeof(inputs[i]) > 0) {
      turns = inputs[i].substr (1);
    }
    else
      turns = "0";
    int iTurns = stoi(turns);
    
    // If going right
    if (direction == 'R') {
      if (iTurns > (100)) {
        int zerosPassed = iTurns / 100;
        zeroCounter += zerosPassed;
        iTurns = iTurns % 100;
        // << "R/>" << zerosPassed << "\n";
      }
      dialLoc = dialLoc + iTurns;
      // If rotated past 99 return to 0
      if (dialLoc > 99) {
        dialLoc = dialLoc - 100; 
        zeroCounter++;
        //cout << "R+0\n";
      }
    }
    else if (direction =='L') {
      if (iTurns > (100)) {
        int zerosPassed = iTurns / 100;
        zeroCounter += zerosPassed;
        iTurns = iTurns % 100;
        //cout << "L/>" << zerosPassed << "\n";
      }
      if (iTurns > dialLoc) {
        iTurns = iTurns - dialLoc;
        dialLoc = 100 - iTurns;
        zeroCounter++;
        //cout << "L+0\n";
        
      }
      else {
        dialLoc = dialLoc - iTurns;
      }
    }
    else {
      cout << "Invalid direction\n";
    }
    
    // Output new location
    //cout << "The dial is rotated " << inputs[i] << " to point at " << dialLoc << ".\n";
    cout << inputs[i] << ">" << dialLoc << "\n\n";
  }
  
  // Close the file
  MyReadFile.close();
  
  cout << "The password is " << zeroCounter;
    
  return 0;
}
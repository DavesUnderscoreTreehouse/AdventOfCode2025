#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
  // Filepath for input data
  string filepath = "input.txt";
  // Read from the text file
  ifstream f(filepath);
  
  int joltage = 0;
  int biggestNum, i1, i2;
  string inputText, concat;
  
  // for each line
  while (getline(f, inputText)) {
    cout << "Input: " << inputText << "\n";
    biggestNum = 0;
    concat ="";
    
    // find largest 2 digits
    for (int i = 0; i < inputText.length(); i++) {
      char c1 = inputText[i];
      for (int j = 1; j < ((inputText.length()) - i); j++) {
        char c2 = inputText[i + j];
        if ((c1 >= '0' && c1 <= '9') && (c2 >= '0' && c2 <= '9')) {
          i1 = (c1 - '0');
          i2 = (c2 - '0');
          concat = string(1, c1) + c2;
          int num = stoi(concat);
          if (num > biggestNum) {
            biggestNum = num;
          }
        } else {
          // Handle non-numeric characters or errors.
        }
      }
    }
    // sum line value
    joltage += biggestNum;
    cout << "Biggest number: " << biggestNum << "\n";
  }
  
  cout << "Final joltage is: " << joltage;

  return 0;
}
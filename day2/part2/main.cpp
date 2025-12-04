#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
  // Filepath for input data
  string filepath = "../input.txt";
  // Read from the text file
  ifstream f(filepath);

  __int64 num1, num2;
  char dash, comma;
  unsigned __int64 total = 0;
  char end;

  do {
    f >> num1 >> dash >> num2 >> comma;
    
    cout << num1 << "\n";
    cout << num2 << "\n";

    for (__int64 id = num1; id <= num2; id++) {
      string idStr = to_string(id);
      bool invalid = false;
      // remove odd length nums
      if (((idStr.length() % 2) == 0) && (idStr.substr(0, (idStr.length() / 2)) == idStr.substr(idStr.length() / 2, (idStr.length() / 2)))) {
        invalid = true;
      }
      else {
        if (idStr.length() == 3) {
          if ((idStr[0] == idStr[1]) && (idStr[0] == idStr[2])) {
            invalid = true;
          }
        }
        else {
          for (int i = 1; i < idStr.length() / 2; i++) {          // iterate through pattern lengths
            bool part2internalinvalid = true;
            for (int j = 0; j < idStr.length() / i; j++) {        // iterate through positions
              if ((idStr.substr(0, i) == idStr.substr(i * j, i)) && ((idStr.length() % i) == 0)) {
              }
              else {
                part2internalinvalid = false;
              }
            }
            if (part2internalinvalid) {
              invalid = true;
            }
          }
        }
      }
      if (invalid) {
        total += id;
      }
    }
  } 
  while (f.peek() != EOF);
  
  cout << "\nTotal: " << total;
  return 0;
}
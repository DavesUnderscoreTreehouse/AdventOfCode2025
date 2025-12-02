#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
  // Filepath for input data
  string filepath = "../testinput.txt";
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
      bool part1invalid = false;
      bool part2invalid = true;
      // remove odd length nums
      if (((idStr.length() % 2) == 0) && (idStr.substr(0, (idStr.length() / 2)) == idStr.substr(idStr.length() / 2, (idStr.length() / 2)))) {
        part1invalid = true;
        cout << "first if invalid " << idStr << "\n";
      }
      else {
        for (int i = 1; i < idStr.length() / 2; i++) {          // iterate through pattern lengths
          for (int j = 0; j < idStr.length() / i; j++) {        // iterate through positions
            if (idStr.substr(0, i) == idStr.substr(i * j, i)) {
              cout << "Invalid: " << idStr.substr(0,i) << ", " << idStr.substr(i * j, i) << "\n";
            }
            else {
              part2invalid = false;
              cout << "Valid: " << idStr.substr(0,i) << ", " << idStr.substr(i * j, i) << "\n";
            }
          }
          if (part2invalid) {
            part1invalid = true;
            cout << "part 2 override catch\n";
          }
          else {
            cout << "pattern length " << i << " checked\n";
            part2invalid = true;
          }
        }
      }
      if (part1invalid || part2invalid) {
          cout << "Match: " << id << "\n\n";
          total += id;
          //cout << "Total so far: " << total << "\n";6
        }
      else
        cout << "\n";
    }
  } 
  while (f.peek() != EOF);
  
  cout << "\nTotal: " << total;
  return 0;
}
#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
  // Filepath for input data
  string filepath = "input.txt";
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
      // remove odd length nums
      if (((idStr.length() % 2) != 1) && (idStr.substr(0, (idStr.length() / 2)) == idStr.substr(idStr.length() / 2, (idStr.length() / 2)))) {
        cout << "Match: " << id << "\n";
        total += id;
        cout << "Total so far: " << total << "\n";
      }
    }
  } 
  while (f.peek() != EOF);
  
  cout << "\nTotal: " << total;
  return 0;
}
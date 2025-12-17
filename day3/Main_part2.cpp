#include <iostream>
#include <fstream>
using namespace std;

std::string trim(const std::string& line)
{
    const char* WhiteSpace = " \t\v\r\n";
    std::size_t start = line.find_first_not_of(WhiteSpace);
    std::size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : line.substr(start, end - start + 1);
}

int main() 
{
  char c1, c2;
  int lineCount, lowDigit, runCount, i1, i2;
  long long int bankJoltage, totalJoltage;
  string filepath, inputText;
  
  filepath = "input.txt";
  ifstream f(filepath);
  
  lineCount = 0;
  while (getline(f, inputText)) {
    lineCount++;
  }
  cout << "Line count: " << lineCount << "\n\n";
  
  f.clear();
  f.seekg(0, ios::beg);
  
  string banks[lineCount];
  lineCount = 0;
  while (getline(f, inputText)) {
    banks[lineCount] = inputText;
    //cout << banks[lineCount] << "\n";
    lineCount++;
  }
  cout << "\n";
  
  totalJoltage = 0;
  for (string bank : banks) {
    bank = trim(bank);
    cout << bank << "\n";
    //until bank has 12 batteries
    runCount = 0;
    while ((bank.length() > 12)) {
      lowDigit = -1;
      for (int i = 0; i < bank.length(); i++) {
        // if first digit less than second, remove and break
        // else if at last digitcontinue
        c1 = bank[i];
        c2 = bank[i + 1];
        i1 = (c1 - '0');
        i2 = (c2 - '0');
        if (i1 < i2) {
          lowDigit = i;
          //cout << "Break" << "\n";
          break;
        } else if (i + 1 == bank.length()) { //(lowDigit == -1) && 
          lowDigit = i;
          //cout << "Last digit" << "\n";
        }
      }
      //cout << "First string: " << bank.substr(0, lowDigit) << "\nSecond string: " << bank.substr((lowDigit + 1), (bank.length() - (lowDigit + 1))) << "\n";
      bank = (bank.substr(0, lowDigit) + bank.substr((lowDigit + 1), (bank.length() - (lowDigit + 1))));
      runCount++;
      //cout << "Run count: " << runCount << "\t Bank: " << bank << "\tLength: " << bank.length() << "  Low digit: " << bank[lowDigit] << "  Index: " << lowDigit << "\n\n";
    }
    totalJoltage += stoll(bank);
    cout << "\n";
  }
  cout << "Total joltage = " << totalJoltage << "\n";
}




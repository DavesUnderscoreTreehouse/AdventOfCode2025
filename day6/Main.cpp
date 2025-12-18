#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

std::string trim(const std::string& line)
{
    const char* WhiteSpace = " \t\v\r\n";
    std::size_t start = line.find_first_not_of(WhiteSpace);
    std::size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : line.substr(start, end - start + 1);
}

struct Sum {
    int num[4];
    char sign;
};

int main() 
{
    char lastChar;
    int lineCount, found[5];
    long long int sumTotal, total;
    string filepath, s_input, sepInput;
    string lines[5];
    vector<Sum> sums;
    
    filepath = "input.txt";
    ifstream f(filepath);
    
    lineCount = 0;
    lines[4] = "";
    while (getline(f, s_input)) {
        lines[lineCount] = s_input;
        lineCount++;
    }
    
    do {
        Sum sum;
        for (int i = 0; i < lineCount; i++) {
            if (lines[i] == "")
                break;
            lastChar = lines[i][lines[i].length()];
            if (i == lineCount - 1)
                lines[lineCount - 1] = lines[lineCount - 1] + lastChar;
            lines[i] = trim(lines[i]);
            found[i] = lines[i].find(' ');
            sepInput = lines[i].substr(0, found[i]);
            if (found[i] != string::npos)
                lines[i] = lines[i].substr(found[i], string::npos);
            
            if (sepInput.length() > 1)
                sepInput = trim(sepInput);
            
            if (i == lineCount - 1)
                sum.sign = sepInput[0];
            else
                sum.num[i] = stoi(sepInput);
        }
        sums.push_back(sum);
    } while (found[0] != string::npos);
    
    total = 0;
    for (Sum sum : sums) {
        if (sum.sign == '+') {
            sumTotal = 0;
            for (int i = 0; i < lineCount - 1; i++)
                sumTotal += sum.num[i];
        } else if (sum.sign == '*') {
            sumTotal = 1;
            for (int i = 0; i < lineCount - 1; i++)
                sumTotal = sumTotal * sum.num[i];
        }
        total += sumTotal;
    }
    
    cout << "Check total: " << total << "\n";
    return 0;
}


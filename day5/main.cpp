#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    int found, freshCount;
    string filepath, s_input, rangeBegin, rangeEnd;
    bool counted;
    vector<long long int> range, ids;
    vector<vector<long long int>> rangeRanges;
    filepath = "input.txt";

    ifstream f(filepath);
    
    // count lines

    cout << "Ranges\n";
    cout << "Start \t| End\n";
    while (getline(f, s_input)) {
        range.erase(range.begin(), range.end());
        found = s_input.find("-");
        // if "-"" found
        if (found != std::string::npos) {
            rangeBegin = s_input.substr(0, found);
            rangeEnd = s_input.substr(found + 1, (s_input.length() - found));
            range.push_back(stoll(rangeBegin));
            range.push_back(stoll(rangeEnd));
            rangeRanges.push_back(range);

            cout << rangeBegin << "\t| " << rangeEnd << "\n";
        } else {
            try {
                ids.push_back(stoll(s_input));
                //cout << "Ingredient " << ids.at(ids.size() - 1) << " added\n";
            } catch (const invalid_argument& ia) {
                cerr << "Falied conversion, invalid arguement: " << ia.what() << "\n";
            }
        }
    }

    // check ids in ranges
    freshCount = 0;
    for (long long int i : ids) {
        counted = false;
        for (vector<long long int> r : rangeRanges) {
            if ((i >= r.at(0)) && (i <= r.at(1)) && (counted == false)) {
                freshCount++;
                counted = true;
                cout << "Ingredient " << i << " is fresh and included in range: " << r.at(0) << "-" << r.at(1) << "\n";
            }
        }
    }
    cout << "\n" << freshCount << " of the ingredients are fresh." ;
    return 0;
}
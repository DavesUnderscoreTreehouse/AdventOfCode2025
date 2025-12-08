#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int found;
    unsigned __int64 freshCount, rangeMin, rangeMax;
    string filepath, s_input, rangeBegin, rangeEnd;
    vector<unsigned __int64> range, ids, freshIds;
    vector<vector<unsigned __int64>> rangeRanges;
    filepath = "testinput_part2.txt";

    ifstream f(filepath);
    
    // count lines

    //cout << "Ranges\n";
    //cout << "Start \t| End\n";
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
            //cout << rangeBegin << "\t| " << rangeEnd << "\n";
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
    rangeMin = 0;
    rangeMin = 0;
    
    // for each range
    unsigned __int64 rIndex = 0;
    for (vector<unsigned __int64> r : rangeRanges) {
        // check if max or min within each range
        cout << "Range: " << r.at(0) << " - " << r.at(1) << "\n";
        unsigned __int64 rCheckIndex = 0;
        for (vector<unsigned __int64> rCheck : rangeRanges) {
            cout << "Check range: " << rCheck.at(0) << " - " << rCheck.at(1) << "\n";
            // check overlap:
            // for each range, check if overlapping another range
            //  if range has lower overlap with check range, change range max to check range max value
            if ((r.at(0) <= rCheck.at(0)) && (r.at(1) >= rCheck.at(0)) && (r.at(1) <= rCheck.at(1))) { 
                rangeRanges.at(rIndex).at(1) = rCheck.at(1);
                cout << "Lower overlap\n";
                //cout << "Range lower overlap\n";
            }
            //  and if range has upper overlap with check range, change range min to check range min value
            if ((r.at(1) >= rCheck.at(1)) && (r.at(0) >= rCheck.at(0)) && (r.at(0) <= rCheck.at(1))) {
                rangeRanges.at(rIndex).at(0) = rCheck.at(0);
                cout << "Upper overlap\n";
                //cout << "Range upper overlap\n";
            }
            try {
                if ((rangeRanges.at(rIndex).at(0) <= rCheck.at(0)) && (rangeRanges.at(rIndex).at(1) >= rCheck.at(1))) {
                    rangeRanges.at(rCheckIndex).at(0) = 0;
                    rangeRanges.at(rCheckIndex).at(1) = 0;
                }
            } catch (const out_of_range& oor) {
                cerr << "Range erase: Out of range error at index" << rCheckIndex << ": " << oor.what() << "\n";
            }
            cout << "Output range post-check: " << rangeRanges.at(rIndex).at(0) << " - " << rangeRanges.at(rIndex).at(1) << "\n";
            rCheckIndex++;
        }
        cout << "Output range post-allcheck: " << rangeRanges.at(rIndex).at(0) << " - " << rangeRanges.at(rIndex).at(1) << "\n\n";
        rIndex++;
    }

    for (vector<unsigned __int64> r : rangeRanges) {
        cout << "Range min: " << r.at(0) << "\t| Range max: " << r.at(1) << "\n";
        freshCount += ((r.at(1) + 1) - r.at(0));
        // // overwrite IDs with all numbers within range
        // try {
        //     ids.erase(ids.begin(), ids.end());
        //     for (unsigned __int64 i = r.at(0); i <= r.at(1); i++) {
        //         ids.push_back(i);
        //     }
        // } catch (const bad_alloc& ba) {
        //     cerr << "Bad allocation: " << ba.what() << "\n";
        // }
        // for (unsigned __int64 i : ids) {
        //     freshIds.push_back(0);
        //     result = find(freshIds.begin(), freshIds.end(), i);
        //     if ((i >= r.at(0)) && (i <= r.at(1)) && (result != freshIds.end())) {
        //         freshIds.pop_back();
        //         freshIds.push_back(i);
        //         freshCount++;
        //         //cout << "Ingredient " << i << " is fresh and included in range: " << r.at(0) << "-" << r.at(1) << "\n";
        //     }
        // }
    }
    cout << "\n" << freshCount << " of the ingredients are fresh." ;
    return 0;
}
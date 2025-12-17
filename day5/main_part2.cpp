#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Range {
    long long int min, max;
};

bool range_sorter(Range const& lhs, Range const& rhs) {
    if (lhs.min != rhs.min)
        return lhs.min < rhs.min;
    if (lhs.max != rhs.max)
        return lhs.max < rhs.max;
    return false;
}

int main() {
    int lineCount, found;
    long long int freshIngredients;
    string filepath, s_input, s_min, s_max;
    Range oldRange;
    vector<Range> newRanges;
    
    filepath = "input_part2.txt";
    ifstream f(filepath);

    lineCount = 0;
    while (getline(f,s_input)) {
        lineCount++;
    }
    cout << "Line count: " << lineCount << "\n";
    Range ranges[lineCount];
    
    // reset file pointer
    f.clear();
    f.seekg(ios::beg);

    lineCount = 0;
    while (getline(f, s_input)) {
        Range range;
        found = s_input.find("-");
        s_min = s_input.substr(0, found);
        s_max = s_input.substr(found + 1, (s_input.length() - found));
        range.min = stoll(s_min);
        range.max = stoll(s_max);
        ranges[lineCount] = range;
        lineCount++;
    }
    
    // sort ranges
    sort(ranges, ranges + lineCount, range_sorter);

    // collapse ranges
    oldRange = {0, 0};
    for (int i = 0; i < (sizeof(ranges) / sizeof(ranges[0])); i++) {
        if (ranges[i].max <= oldRange.max) {
            // full overlap
            // erease range, compare next range
            ranges[i] = {0,0};
        } else if (ranges[i].max > oldRange.max) {
            if (ranges[i].min > oldRange.max) {
                // no overlap
                // add oldRange to list of new ranges move to next range
                newRanges.push_back(oldRange);
                oldRange = ranges[i];
            } else if (ranges[i].min <= oldRange.max) {
                // upper overlap
                oldRange.max = ranges[i].max;
                ranges[i] = {0,0};
            }
            else {
                cout << "Unexpected range situation occured at line " << i << "\n";
            }
        } else {
            cout << "Unexpected range situation occured at line " << i << "\n";
        }
        if ((i + 1) == (sizeof(ranges) / sizeof(ranges[0]))) {
            newRanges.push_back(oldRange);
        }
    }
    
    // collapsed sorted ranges
    //cout << "\nRanges:\n" << "Min\t| Max\n";
    //for (Range range : ranges) {
    //    cout << range.min << "\t| " << range.max << "\n";
    //}
    //cout << "\nNew ranges:\n" << "Min\t| Max\n";
    //for (Range range : newRanges) {
    //    cout << range.min << "\t| " << range.max << "\n";
    //}
    
    // count number of ID within total range (difference)
    freshIngredients = 0;
    for (Range range : newRanges) {
        if (range.min == 0 && range.max == 0) {
            continue;
        } else {
            freshIngredients += range.max - range.min + 1;
        }
    }
    
    cout << "\nThere are " << freshIngredients << " fresh ingredient IDs.";
    
    return 0;
}





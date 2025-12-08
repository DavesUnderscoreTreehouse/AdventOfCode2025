#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Range {
    unsigned __int64 min, max;

    bool range_sorter(Range const& lhs, Range const& rhs) {
        if (lhs.min != rhs.min)
            return lhs.min < rhs.min;
        if (lhs.max != rhs.max)
            return lhs.max < rhs.max;
        return false;
    }
};

int main() {
    int lineCount, found;
    string filepath, s_input, s_min, s_max;
    Range oldRange;

    filepath = "testinput_part2.txt";
    ifstream f(filepath);

    lineCount = 0;
    while (getline(f,s_input)) {
        lineCount++;
    }
    Range ranges[lineCount];

    // reset file pointer
    f.clear();
    f.seekg(ios::beg);

    lineCount = 0;
    cout << "Ranges:\n";
    cout << "Min\t| Max\n";
    while (getline(f, s_input)) {
        Range range;
        found = s_input.find("-");
        s_min = s_input.substr(0, found);
        s_max = s_input.substr(found + 1, (s_input.length() - found));
        range.min = stoll(s_min);
        range.max = stoll(s_max);
        ranges[lineCount] = range;
        lineCount++;
        cout << s_min << "\t| " << s_max << "\n";
    }

    // sort ranges
    sort(ranges.begin(), ranges.end(), range_sorter);

    // collapse ranges
    oldRange = {0, 0};
    for (int i = 0; i < (sizeof(ranges) / sizeof(ranges[0])); i++) {
        Range range = ranges[i];
        // if oldRange max within range, 
        if ((range.min <= oldRange.max) && (range.max >= oldRange.max)) {

        }
    }
    return 0;
}
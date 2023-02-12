//
// Created by Женя on 12.02.2023.
// press f
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct NumberComparator {
    bool operator()( const string& lx, const string& rx ) {
        int l = lx.length();
        int r = rx.length();
        int min = l < r ? l : r;
        for (int i = 0; i < min; i++) {
            if (lx.at(i) < rx.at(i)) {
                return true;
            }
        }
        if (l == r) return false;
        int max = l > r ? l : r;
        for (int i = min; i < max; i++) {
            if (l > r) {
                if (lx.at(i) < lx.at(i - r)) {
                    return true;
                }
            } else {
                if (rx.at(i - l) < rx.at(i)) {
                    return true;
                }
            }
        }
        for (int i = max; i < l + r; i++) {
            if (l > r) {
                if (rx.at(i - l) < lx.at(i - r)) {
                    return true;
                }
            } else {
                if (rx.at(i - l) < lx.at(i - r)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    vector<string> numbers;
    numbers.resize(100);
    string line;
    while (cin >> line) {
        if (line.at(0)=='/') break;
        numbers.push_back(line);
    }
    sort(numbers.begin(), numbers.end(), NumberComparator());
    for (vector<string>::iterator it = numbers.end(); it != numbers.begin(); it--) {
        cout << *it;
    }
}

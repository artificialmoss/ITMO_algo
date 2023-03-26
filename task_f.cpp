//
// Created by Женя on 12.02.2023.
// press f
//

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

struct NumberComparator {
    bool operator()( const string& lx, const string& rx ) {
        int l = lx.length();
        int r = rx.length();
        int min = l < r ? l : r;
        for (int i = 0; i < min; i++) {
            if (lx.at(i) > rx.at(i)) {
                return true;
            }
            if (lx.at(i) < rx.at(i)) {
                return false;
            }
        }
        if (l == r) return false;
        int max = l > r ? l : r;
        for (int i = min; i < max; i++) {
            if (l > r) {
                if (lx.at(i) > lx.at(i - r)) {
                    return true;
                }
                if (lx.at(i) < lx.at(i - r)) {
                    return false;
                }
            } else {
                if (rx.at(i - l) > rx.at(i)) {
                    return true;
                }
                if (rx.at(i - l) < rx.at(i)) {
                    return false;
                }
            }
        }
        for (int i = max; i < l + r; i++) {
            if (rx.at(i - l) > lx.at(i - r)) {
                return true;
            }
            if (rx.at(i - l) < lx.at(i - r)) {
                return false;
            }
        }
        return false;
    }
};

int main() {
    deque<string> numbers;
    string line;
    while (cin >> line) {
        numbers.push_back(line);
    }
    sort(numbers.begin(), numbers.end(), NumberComparator());
    for (deque<string>::iterator it = numbers.begin(); it != numbers.end(); it++) {
        cout << *it;
    }
}

//
// Created by Женя on 03.04.2023.
//

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void print_window(const deque<pair<int, int>>& window) {
    for (auto it = window.begin(); it != window.end(); it++) {
        cout << "[" << it->first << ", " << it->second << "] ";
    }
    cout << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    deque<pair<int, int>> window;
    int length = 0;
    int cur;
    for (int i = 1; i <= n; i++) {
        cin >> cur;
        while (length > 0 && window.back().second >= cur) {
            window.pop_back();
            length--;
        }
        window.push_back(make_pair(i, cur));
        length++;
        if (i >= k) {
            if (window.front().first + k <= i) {
                window.pop_front();
                length--;
            }
            cout << window.front().second << " ";
        }
    }
}
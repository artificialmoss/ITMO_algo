//
// Created by Женя on 09.02.2023.
//

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    deque<int> rooms;

    for (int i  = 0; i < n; i++) {
        int a;
        cin >> a;
        rooms.push_back(a);
    }
    sort(rooms.begin(), rooms.end());
    while (n > k) {

    }
}
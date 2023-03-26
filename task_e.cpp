//
// Created by Женя on 09.02.2023.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool arrange_cows_with_fixed_distance(vector<int> rooms, int cows, int min_dist) {
    int count = 1;
    int prev_room = rooms.at(0);
    if (count == cows) {
        return true;
    }
    for (vector<int>::iterator i = rooms.begin(); i != rooms.end(); i++) {
        if (*i - prev_room >= min_dist) {
            count++;
            prev_room = *i;
        }
        if (count == cows) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> rooms;
    rooms.resize(n);
    for (int i  = 0; i < n; i++) {
        cin >> rooms.at(i);
    }

    int l = 1, r = rooms.at(n - 1) - rooms.at(0) + 1;
    int dist;

    while (l + 1 < r) {
        dist = (l + r) / 2;
        if (arrange_cows_with_fixed_distance(rooms, k, dist)) {
            l = dist;
        } else {
            r = dist;
        }
    }

    cout << l;

}
//
// Created by Женя on 01.03.2023.
//

#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    int n, k, p;
    cin >> n >> k >> p;
    vector<deque<int>> cars = vector<deque<int>>(n + 1);
    vector<int> order = vector<int>(p);
    for (int i = 1; i < n + 1; i++) {
        cars[i] = deque<int>();
    }
    for (int i = 0; i < p; i++) {
        cin >> order[i];
        cars[order[i]].push_back(i);
    }
    for (int i = 1; i < n + 1; i++) {
        if (!cars[i].empty()) {
            cars[i].pop_front();
        }
        cars[i].push_back(p);
    }

    unordered_set<int> floor_set = unordered_set<int>();
    priority_queue<int> floor_positions = priority_queue<int>();
    int floor_count = 0;
    int ops_count = 0;
    for (int i = 0; i < p; i++) {
        int cur = order[i];
        if (floor_set.find(cur) == floor_set.end()) {
            // машины ещё нет на полу, нужно найти самую дальнюю если больше к, снести её и заменить
            if (floor_count >= k) {
                int pos = floor_positions.top();
                floor_positions.pop();
                if (pos != p) {
                    floor_set.erase(order[pos]); //average->const, worst -> n
                }
                floor_count--;
            }
            floor_set.insert(cur);
            floor_count++;
            ops_count++;
        }
        floor_positions.push(cars[cur].front());
        cars[cur].pop_front();
    }
    cout << ops_count << endl;
}
//
// Created by Женя on 21.05.2023.
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;

const unsigned long long INF = ULLONG_MAX;

int weight(string a, string b) {
    int max_pref = 0;
    while (max_pref < 10) {
        if (a[max_pref] != b[max_pref]) {
            break;
        } else {
            max_pref++;
        }
    }
    int dif_count = 1;
    for (int j = max_pref + 1; j < 10; j++) {
        if (a[j] != b[j]) {
            if (dif_count > 1 || a[j] != b[max_pref] || b[j] != a[max_pref]) {
                return -1;
            }
            dif_count++;
        }
    }
    return max_pref;
}

vector<pair<string, int>> generate_numbers(string number) {
    vector<pair<string, int>> numbers;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j + '0' != number.at(i)) {
                string number1 = string(number);
                number1[i] = j + '0';
                numbers.push_back({number1, i});
            }
        }
    }
    for (int i = 0; i < 10 - 1; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (number[i] != number[j]) {
                string number1 = string(number);
                number1[i] = number[j];
                number1[j] = number[i];
                numbers.push_back({number1, i});
            }
        }
    }
    return numbers;
}

void relax(vector<unsigned long long>& ways, vector<int>& parents, int v, int to, int weight, priority_queue<pair<unsigned long long, int>>& level) {
    int prev_way = ways[to];
    ways[to] = min(ways[to], ways[v] + weight);
    if (ways[to] < prev_way) {
        level.push({-ways[to], to});
        parents[to] = v;
    }
}

void dijkstra(vector<string>& phones, unordered_map<string, int>& ids, vector<unsigned long long>& ways, priority_queue<pair<unsigned long long, int>>& level, vector<int>& parents, int dst, vector<int>& times) {
    while (!level.empty()) {
        int idx = level.top().second;
        unsigned long long d = -(level.top().first);
        level.pop();
        if (d >= INF) {
            return;
        }
        if (d > ways[idx]) {
            continue;
        }
        if (idx == dst) {
            return;
        }
        vector<pair<string, int>> neighbours = generate_numbers(phones[idx]);
        for (auto n: neighbours) {
            auto it = ids.find(n.first);
            if (it != ids.end()) {
                int i = it->second;
                int w = times[n.second];
                relax(ways, parents, idx, i, w, level);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> times(10);
    vector<string> phones(n);
    unordered_map<string, int> ids;

    for (int i = 0; i < 10; i ++) {
        cin >> times[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> phones[i];
        ids[phones[i]] = i;
    }

    vector<unsigned long long> ways(n, INF);
    ways[0] = 0;
    vector<int> parents(n, -1);
    priority_queue<pair<unsigned long long, int>> q;
    q.push({0, 0});

    dijkstra(phones, ids, ways, q, parents, n - 1, times);

    if (ways[n - 1] >= INF) {
        cout << -1 << endl;
    } else {
        cout << ways[n - 1] << endl;
        deque<int> way;
        int cur = n - 1;
        int size = 0;
        while (cur != 0) {
            way.push_front(cur);
            cur = parents[cur];
            size++;
        }
        way.push_front(cur);
        size++;
        cout << size << endl;
        auto prev = way.begin();
        while (prev != way.end()) {
            cout << *prev + 1 << " ";
            prev++;
        }
    }
}

//
// Created by Женя on 25.04.2023.
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int invert_color(int color) {
    return (color == 1) ? 2 : 1;
}

int main() {
    int v, e;
    cin >> v >> e;
    if (e == 0) {
        cout << "YES" << endl;
        return 0;
    }
    vector<vector<int>> graph(v);
    vector<int> colors(v);
    for (int i = 0; i < v; i++) {
        graph[i].resize(v);
    }
    unordered_set<int> used_vertexes;
    for (int i = 0; i < e; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--;
        graph[v2][v1] = 1;
        graph[v1][v2] = 1;
        used_vertexes.insert(v1);
        used_vertexes.insert(v2);
    }

    unordered_set<int> cur_level;
    unordered_set<int> prev_level;

    while (!used_vertexes.empty()) {
        if (prev_level.empty()) {
            int cur_vertex = *used_vertexes.begin();
            colors[cur_vertex] = 1;
            prev_level.insert(cur_vertex);
        }
        for (auto it : prev_level) {
            int prev_color = colors[it];
            for (int i = 0; i < v; i++) {
                if (graph[it][i] == 1) {
                    if (colors[i] == prev_color) {
                        cout << "NO" << endl;
                        return 0;
                    }
                    if (colors[i] == 0) {
                        colors[i] = invert_color(prev_color);
                        cur_level.insert(i);
                    }
                }
            }
            used_vertexes.erase(it);
        }
        prev_level = cur_level;
        cur_level = {};
    }

    cout << "YES" << endl;
}

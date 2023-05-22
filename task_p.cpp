//
// Created by Женя on 07.05.2023.
// tl 7 unfortunately
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs_input_tree(int start, int n, vector<vector<int>>& graph, vector<bool>& visited, int v, int max_weight) {
    visited[start] = true;
    v++;
    for (int i = 0; i < n; i++) {
        if (graph[start][i] > 0 && graph[start][i] <= max_weight && !visited[i]) {
            v = dfs_input_tree(i, n, graph, visited, v, max_weight);
        }
    }
    return v;
}

int dfs_output_tree(int start, int n, vector<vector<int>>& graph, vector<bool>& visited, int v, int max_weight) {
    visited[start] = true;
    v++;
    for (int i = 0; i < n; i++) {
        if (graph[i][start] > 0 && graph[i][start] <= max_weight && !visited[i]) {
            v = dfs_output_tree(i, n, graph, visited, v, max_weight);
        }
    }
    return v;
}

bool check_volume(int n, vector<vector<int>>& graph, int volume) {
    vector<bool> visited(n, false);
    int sum = dfs_input_tree(0, n, graph, visited, 0, volume);
    visited = vector<bool>(n, false);
    sum += dfs_output_tree(0, n, graph, visited, 0, volume);
    return (sum == 2*n);
}

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    int INF = 1e9 + 1;
    int min = INF;
    int max = -1;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        graph[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] > max) {
                max = graph[i][j];
            }
            if (i == j) {
                graph[i][j] = INF;
            }
            if (graph[i][j] < min) {
                min = graph[i][j];
            }
        }
    }

    int l = min - 1;
    int r = max;

    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check_volume(n, graph, m)) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r << endl;
}
//
// Created by Женя on 20.05.2023.
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(int start, int n, int component_id, vector<vector<int>>& graph, vector<int>& components) {
    components[start] = component_id;
    for (int i = 0; i < n; i++) {
        if (graph[start][i] == 1 && components[i] != component_id) {
            dfs(i, n, component_id, graph, components);
        }
    }
}

int get_unvisited_vertex(vector<int>& components) {
    for (int i = 0; i < components.size(); i++) {
        if (components[i] == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        graph[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cur--;
        graph[cur][i] = 1;
    }
    vector<int> components(n);
    int start = get_unvisited_vertex(components);
    int comp_id = 1;
    while(start != -1) {
        dfs(start, n, comp_id, graph, components);
        comp_id++;
        start = get_unvisited_vertex(components);
    }

    unordered_set<int> comps = unordered_set<int>();

    for (auto it: components) {
        comps.insert(it);
    }

    cout << comps.size() << endl;
}
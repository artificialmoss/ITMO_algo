//
// Created by Женя on 29.05.2023.
// lab homework - rewrite with bfs
//

#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;

enum states {
    LAND, FOREST, WATER, NONE
};

const int INF = 2*1000*1000 + 2;

enum states match_state(char c) {
    switch (c) {
        case '.' : return LAND;
        case 'W' : return FOREST;
        case '#' : return WATER;
        default: return NONE;
    }
}

int get_dist(int a, int b) {
    if (a == WATER || b == WATER) {
        return 0;
    }
    if (b == FOREST) {
        return 2;
    }
    return 1;
}

struct vertex {
    int id;
    int north_edge;
    int south_edge;
    int east_edge;
    int west_edge;
};

void build_graph(vector<vector<int>>& land, vector<struct vertex>& graph, int m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            graph[i*m+j].id = i*m + j;
            if (i > 0) {
                int dist = get_dist(land[i][j], land[i-1][j]);
                graph[i*m+j].north_edge = dist;
            }
            if (i < n - 1) {
                int dist = get_dist(land[i][j], land[i+1][j]);
                graph[i*m+j].south_edge = dist;
            }
            if (j > 0) {
                int dist = get_dist(land[i][j], land[i][j-1]);
                graph[i*m+j].west_edge = dist;
            }
            if (j < m - 1) {
                int dist = get_dist(land[i][j], land[i][j+1]);
                graph[i*m+j].east_edge = dist;
            }
        }
    }
}

char match_direction(int prev_id, int cur_id) {
    if (prev_id > cur_id) {
        if (prev_id - cur_id == 1) {
            return 'W';
        }
        return 'N';
    }
    if (cur_id - prev_id == 1) {
        return 'E';
    }
    return 'S';
}

void bfs(vector<struct vertex>& graph, vector<int>& ways, vector<int>& parents, int root_id, int dest_id, int m) {
    set<int> cur_level;
    set<int> prev_level;
    set<int> next_level;
    prev_level.insert(root_id);
    while (!prev_level.empty()) {
        for (auto v: prev_level) {
            if (graph.at(v).south_edge > 0 && ways[v + m] == INF) {
                if (graph.at(v).south_edge == 1) {
                    cur_level.insert(v + m);
                } else {
                    next_level.insert(v + m);
                }
                ways[v + m] = ways[v] + graph.at(v).south_edge;
                parents[v + m] = v;
                if (v + m == dest_id) {
                    return;
                }
            }
            if (graph.at(v).north_edge > 0 && ways[v - m] == INF) {
                if (graph.at(v).north_edge == 1) {
                    cur_level.insert(v - m);
                } else {
                    next_level.insert(v - m);
                }
                ways[v - m] = ways[v] + graph.at(v).north_edge;
                parents[v - m] = v;
                if (v - m == dest_id) {
                    return;
                }
            }
            if (graph.at(v).west_edge > 0 && ways[v - 1] == INF) {
                if (graph.at(v).west_edge == 1) {
                    cur_level.insert(v - 1);
                } else {
                    next_level.insert(v - 1);
                }
                ways[v - 1] = ways[v] + graph.at(v).west_edge;
                parents[v - 1] = v;
                if (v - 1 == dest_id) {
                    return;
                }
            }
            if (graph.at(v).east_edge > 0 && ways[v + 1] == INF) {
                if (graph.at(v).east_edge == 1) {
                    cur_level.insert(v + 1);
                } else {
                    next_level.insert(v + 1);
                }
                ways[v + 1] = ways[v] + graph.at(v).east_edge;
                parents[v + 1] = v;
                if (v + 1 == dest_id) {
                    return;
                }
            }
        }
        prev_level = cur_level;
        cur_level = next_level;
        next_level = {};
        if (prev_level.empty()) {
            prev_level = cur_level;
            cur_level = next_level;
            next_level = {};
        }

//        for (int i = 0; i < ways.size(); i++) {
//            cout << i << " " << ways[i] << ", ";
//        }
//        cout << endl;
    }
}

int main() {
    int n, m; // n -> rows, m -> cols
    cin >> n >> m;
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;
    x0--;
    y0--;
    x1--;
    y1--;

    vector<struct vertex> graph(n*m, {-1, -1, -1, -1, -1});

    vector<int> ways(n*m, INF);
    ways[x0 * m + y0] = 0;
    vector<vector<int>> land(n);
    string line;
    for (int i = 0; i < n; i++) {
        cin >> line;
        for (char c : line) {
            enum states state = match_state(c);
            if (state != NONE) {
                land[i].push_back(state);
            }
        }
    }
    build_graph(land, graph, m, n);

    vector<int> parents(n*m, -1);

    bfs(graph, ways, parents, x0*m + y0, x1 * m + y1, m);

    if (ways[x1 * m + y1] >= INF) {
        cout << -1 << endl;
    } else {
        cout << ways[x1*m + y1] << endl;
        deque<int> way;
        int cur = x1*m + y1;
        while (cur != x0 * m + y0) {
            way.push_front(cur);
            cur = parents[cur];
        }
        way.push_front(cur);
        auto prev = way.begin();
        auto next = way.begin();
        while (next != way.end()) {
            next++;
            if (next != way.end()) {
                cout << match_direction(*prev, *next);
                prev++;
            }
        }
    }
}
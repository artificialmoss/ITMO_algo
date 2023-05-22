#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <queue>

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

void relax(vector<int>& ways, vector<int>& parents, int v, int to, int weight, priority_queue<pair<int, int>>& level) {
    int prev_way = ways[to];
    ways[to] = min(ways[to], ways[v] + weight);
    if (ways[to] < prev_way) {
        level.push({-ways[to], to});
        parents[to] = v;
    }
}

void dijskra(vector<struct vertex>& graph, vector<int>& ways, priority_queue<pair<int, int>>& level, vector<int>& parents, int m, int n, int dst) {
    while (!level.empty()) {
        int idx = level.top().second;
        int d = -(level.top().first);
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
        if (graph[idx].south_edge != 0) {
            relax(ways, parents, idx, idx + m, graph[idx].south_edge, level);
        }
        if (graph[idx].north_edge != 0) {
            relax(ways, parents, idx, idx - m, graph[idx].north_edge, level);
        }
        if (graph[idx].west_edge != 0) {
            relax(ways, parents, idx, idx - 1, graph[idx].west_edge, level);
        }
        if (graph[idx].east_edge != 0) {
            relax(ways, parents, idx, idx + 1, graph[idx].east_edge, level);
        }
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

    vector<struct vertex> graph(n*m, {-1, 0, 0, 0, 0});

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

    priority_queue<pair<int, int>> q;
    q.push({0, x0*m + y0});

    dijskra(graph, ways, q, parents, m, n, x1*m + y1);

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

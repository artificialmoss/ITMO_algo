//
// Created by Женя on 21.05.2023.
//

#include <iostream>
#include <vector>

using namespace std;

double INF = 1e10;
double eps = 1e-10;

struct edge {
    int a, b;
    double r, c;
};

int main() {
    int n, m, s;
    double v;
    cin >> n >> m >> s >> v;
    vector<double> money(n);
    s--;
    money[s] = v;
    vector<struct edge> edges;
    for (int i = 0; i < m; i++) {
        int a, b;
        double rab, rba, cab, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;
        a--;
        b--;
        edges.push_back({a, b, rab, cab});
        edges.push_back({b, a, rba, cba});
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < 2*m; j++) {
            money[edges[j].b] = max(money[edges[j].b], (money[edges[j].a] - edges[j].c)*edges[j].r);
        }
    }
    for (int i = 0; i < 2*m; i++) {
        if ((money[edges[i].a] - edges[i].c) * edges[i].r - money[edges[i].b] > eps) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}
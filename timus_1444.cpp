//
// Created by Женя on 26.03.2023.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <deque>
#include <algorithm>
#include <math.h>

using namespace std;

const double EPS = 1e-10;

struct point {
    int id;
    int x;
    int y;
    double degree;
    int square_dist;
};

bool is_bigger(struct point cur, struct point prev_max) {
    if (cur.x != prev_max.x) {
        return cur.x < prev_max.x;
    }
    return cur.y < prev_max.y;
}

void print_deque(const deque<struct point>& points, int max_id) {
    for (auto it = points.begin(); it != points.end(); it++) {
        if (it->id == max_id) {
            cout << "[ " << it->id << " ]";
        } else {
            cout << it->id;
        }
        cout << ":" << it->degree << ":" << it->square_dist;
        cout << " ";
    }
    cout << endl;
}

double calc_degree(struct point& focus, struct point& point) {
    int x_dist = focus.x - point.x;
    int y_dist = focus.y - point.y;
    if (x_dist == 0 && y_dist == 0) {
        return -90;
    }
    if (x_dist == 0) {
        return 90;
    }
    return atan((double) y_dist / x_dist) * 180 / M_PI;
}

int calc_square_dist(struct point& focus, struct point& point) {
    int x_dist = focus.x - point.x;
    int y_dist = focus.y - point.y;
    return x_dist * x_dist + y_dist * y_dist;
}

bool compare(struct point& a, struct point& b) {
    if (abs(a.degree - b.degree) > EPS) {
        return (a.degree - b.degree < EPS);
    } else {
        return a.square_dist < b.square_dist;
    }
}
bool change_order(const deque<struct point>& points) {
    struct point last = points.back();
    struct point prev = *(points.end() - 2);
    return (abs(last.degree - prev.degree) < EPS);
}

int main() {
    int n;
    cin >> n;
    deque<struct point> points;
    struct point max;
    struct point cur;
    for (int i = 1; i <= n; i++) {
        int x;
        int y;
        cin >> x >> y;
        cur = (struct point) {
                .id = i,
                .x = x,
                .y = y
        };
        if (i == 1 || is_bigger(cur, max)) {
            max = cur;
        }
        points.push_back(cur);
    }
    for (auto it = points.begin(); it != points.end(); it++) {
        it->degree = calc_degree(max, *it);
        it->square_dist = calc_square_dist(max, *it);
    }
    sort(points.begin(), points.end(), compare);

    //print_deque(points, max.id);

    bool order = change_order(points);
    deque<struct point> last_line;

    if (order) {
        double degree = points.back().degree;
        while (abs(points.back().degree - degree) < EPS) {
            last_line.push_back(points.back());
            points.pop_back();
        }
        for (auto it = last_line.begin(); it != last_line.end(); it++) {
            points.push_back(*it);
        }
    }

    cout << n << endl;

    bool start = false;
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        if (iter->id == 1) {
            start = true;
        }
        if (start) {
            cout << iter->id << endl;
        }
    }
        for (auto iter = points.begin(); iter != points.end(); iter++) {
            if (iter->id == 1) {
                break;
            }
            cout << iter->id << endl;
        }

}

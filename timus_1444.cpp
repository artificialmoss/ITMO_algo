//
// Created by Женя on 17.02.2023.
//

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

const double EPS = 0.000000000000000001;

struct point {
    int id;
    int x;
    int y;
};

double get_tan(int x, int y) {
    if (x == 0 && y == 0) {
        //throw exception();
    }
    return (double) y / x;
}

int get_square_dist(int x, int y) {
    return x*x + y*y;
}

class RelativePointComparator {
    struct point focus;
    int max_x_mult;

public:
    RelativePointComparator(struct point focus) {
        this->focus = focus;
        this->max_x_mult = this->focus.x;
    }

    bool operator()( const struct point& x, const struct point& y) {
        if (focus.id == 0) {
            return false;
        }
        if (x.id == focus.id) {
            return true;
        }
        if (y.id == focus.id) {
            return false;
        }
        int x_dist_1 = focus.x - x.x;
        int x_dist_2 = focus.x - y.x;
        int y_dist_1 = focus.y - x.y;
        int y_dist_2 = focus.y - y.y;
        int sqr_dist1 = get_square_dist(x_dist_1, y_dist_1);
        int sqr_dist2 = get_square_dist(x_dist_2, y_dist_2);
        if (x_dist_1 == 0 && x_dist_2 == 0) {
            return sqr_dist1 < sqr_dist2;
        }
        if (x_dist_1 == 0) {
            return true;
        }
        if (x_dist_2 == 0) {
            return false;
        }
        double tan1 = get_tan(x_dist_1, max_x_mult*(y_dist_1));
        double tan2 = get_tan(x_dist_2, max_x_mult*(y_dist_2));
        if (abs(tan1 - tan2) > EPS) {
            return tan1 - tan2 > EPS;
        }
        return sqr_dist1 < sqr_dist2;



        /*
        if (x_dist_1 != 0 || x_dist_2 != 0) {
            if (x_dist_1 == 0) {
                return true;
            }
            if (x_dist_2 == 0) {
                return false;
            }
            double tan1 = get_tan(x_dist_1, max_x_mult*(y_dist_1));
            double tan2 = get_tan(x_dist_2, max_x_mult*(y_dist_2));
            if (abs(tan1 - tan2) > EPS) {
                return (tan1 - tan2 > EPS);
            }
        }
        int sqr_dist1 = get_square_dist(x_dist_1, y_dist_1);
        int sqr_dist2 = get_square_dist(x_dist_2, y_dist_2);
        return sqr_dist1 < sqr_dist2;*/

    }
};

bool is_bigger(struct point cur, struct point prev_max) {
    if (cur.x != prev_max.x) {
        return cur.x > prev_max.x;
    }
    return cur.y > prev_max.y;
}

void print_deque(const deque<struct point>& points, int max_id) {
    for (auto it = points.begin(); it != points.end(); it++) {
        if (it->id == max_id) {
            cout << "[ " << it->id << " ]";
        } else {
            cout << it->id;
        }
        cout << " ";
    }
    cout << endl;
}

bool change_order(const deque<struct point>& points, struct point max) {
    struct point last = points.back();
    struct point first;
    for (auto it = points.begin(); it != points.end(); it++) {
        if (it->id == 1) {
            first = *it;
        }
    }
    if (abs(get_tan(max.x - first.x, max.y - first.y) - get_tan(max.x - last.x, max.y - last.y)) < EPS) {
        return true;
    }
    return false;
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
    sort(points.begin(), points.end(), RelativePointComparator(max));

    //print_deque(points, max.id);

    bool order = change_order(points, max);
    if (order) {
        reverse(points.begin(), points.end());
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
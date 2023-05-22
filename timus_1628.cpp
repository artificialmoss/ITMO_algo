//
// Created by Женя on 22.04.2023.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    int m, n, k;
    cin >> m >> n >> k;
    // считаем что m строк, n столбцов (оно не влияет на решение, просто зафиксируем, что горизонталей м)
    vector<pair<int, int>> vertical(0), horizontal(0);
    horizontal.push_back(make_pair(1, 0));
    vertical.push_back(make_pair(1, 0));
    for (int i = 0; i < k; ++i) {
        int row, col;
        cin >> row >> col;
        horizontal.push_back(make_pair(row, col));
        vertical.push_back(make_pair(col, row));
    }
    horizontal.push_back(make_pair(m, n + 1));
    vertical.push_back(make_pair(n, m + 1));
    sort(horizontal.begin(), horizontal.end());
    sort(vertical.begin(), vertical.end());

    int stripes = 0;

    int row_prev = 1;
    int col_prev = 0;
    int row_cur, col_cur;
    vector<pair<int, int>> single_points;
    for (int i = 0; i < horizontal.size(); i++) {
        //cout << row_prev << " " << col_prev << " | " << horizontal[i].first << " " << horizontal[i].second;
        row_cur = horizontal[i].first;
        col_cur = horizontal[i].second;
        if (row_cur == row_prev) {
            if (col_cur - col_prev > 2) {
                stripes++;
            }
            if (col_cur - col_prev == 2) {
                single_points.push_back(make_pair(row_cur, col_cur - 1));
            }
        } else {
            // skipped a few (>= 1) rows
            // handle the end of previous row, the ending of the current row, and missing rows

            // missing rows
            if (n != 1) {
                stripes += row_cur - row_prev - 1;
            }
            if (n == 1 && row_cur - row_prev == 2) {
                single_points.push_back(make_pair(row_cur - 1, col_cur));
            }
            // the end of prev row
            if (col_prev < n - 1) {
                stripes++;
            }
            if (col_prev == n - 1) {
                single_points.push_back(make_pair(row_prev, n));
            }
            // the beginning of cur row
            if (col_cur > 2) {
                stripes++;
            }
            if (col_cur == 2) {
                single_points.push_back(make_pair(row_cur, 1));
            }
        }
        col_prev = col_cur;
        row_prev = row_cur;

        //cout << " -> " << stripes << endl;
    }

//    cout << endl;
//    for (auto i : single_points) {
//        cout << i.first << " " << i.second << endl;
//    }

    row_prev = 0;
    col_prev = 1;
    for (int i = 0; i < vertical.size(); i++) {
        row_cur = vertical[i].second;
        col_cur = vertical[i].first;
        //cout << row_prev << " " << col_prev << " | " << row_cur << " " << col_cur;
        if (col_cur == col_prev) {
            if (row_cur - row_prev > 2) {
                stripes++;
            }
            if (row_cur - row_prev == 2) {
                if (find(single_points.begin(), single_points.end(), make_pair(row_cur - 1, col_cur)) != single_points.end()) {
                    stripes++;
                }
            }
        } else {
            // skipped a few (>= 1) rows
            // handle the end of previous row, the ending of the current row, and missing rows

            // missing rows
            if (m != 1) {
                stripes += col_cur - col_prev - 1;
            }
            if (m == 1 && col_cur - col_prev == 2) {
                if (find(single_points.begin(), single_points.end(), make_pair(m, col_cur - 1)) != single_points.end()) {
                    stripes++;
                }
            }
            // the end of prev row
            if (row_prev < m - 1) {
                stripes++;
            }
            if (row_prev == m - 1) {
                if (find(single_points.begin(), single_points.end(), make_pair(m, col_prev)) != single_points.end()) {
                    stripes++;
                }
            }
            // the beginning of cur row
            if (row_cur > 2) {
                stripes++;
            }
            if (row_cur == 2) {
                if (find(single_points.begin(), single_points.end(), make_pair(1, col_cur)) != single_points.end()) {
                    stripes++;
                }
            }
        }
        col_prev = col_cur;
        row_prev = row_cur;

        //cout << " -> " << stripes << endl;
    }



    cout << stripes << endl;
}

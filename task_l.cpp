//
// Created by Женя on 07.03.2023.
//

#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>
#include <random>
#include <array>
#include <list>

using namespace std;

long long calc_left_bound(long long pos, long long k) {
    return max(pos, k - 1);
}

long long calc_right_bound(long long pos, long long k, long long n) {
    return (pos + k - 1 > n - 1) ? n - 1: pos + k - 1;
}

void print_vals_map(map<long long, deque<long long>> values) {
    cout << endl << "=== VALS_MAP ===" << endl;
    for (auto v: values) {
        cout << v.first << ": ";
        for (auto pos: v.second) {
            cout << pos << " ";
        }
        cout << endl;
    }
    cout << "================" << endl << endl;
}

void print_result(int mins[], int n, int k) {
    for (int i = k - 1; i < n; i++) {
        cout << mins[i] << " ";
    }
    cout << endl;
}

long long find_zero_pos(int mins[], int l, int r) {
    if (mins[l] == 0) {
        return l;
    }
    if (mins[r] == 0) {
        return r;
    }
    if (r - l <= 1) {
        return -1;
    }
    int middle = (l + r) / 2;
    int left_search = find_zero_pos(mins, l, middle);
    if (left_search < 0) return find_zero_pos(mins, middle, r);
    return left_search;
}

bool cmp(pair<int, int> a, pair <int, int> b) {
    return a.first < b.first;
}
/*
void build_tree(vector<int>& tree, int src_arr[], int idx, int left, int right) {
    if (left == right) {
        tree.at(idx) = src_arr[left];
        //cout << "leave[" << idx << "] = " << tree[idx] << endl;
        return;
    }
    int middle = (left + right) / 2;
    build_tree(tree, src_arr, 2*idx + 1, middle + 1, right);
    build_tree(tree, src_arr, 2*idx, left, middle);
    tree[idx] = min(tree.at(2*idx), tree.at(2*idx + 1));
    //cout << "tree[" << idx << "] = min(tree[" << 2*idx << "],  tree[" << 2*idx + 1 << "]) = " << tree[idx] << endl;
    return;
}

long long find_min(vector<int> tree, int idx, int tree_l, int tree_r, int l, int r) {
    if (l > r) {
        return INT64_MAX;
    }
    if (l == tree_l && r == tree_r)
        return tree.at(idx);
    int middle = (tree_l + tree_r) / 2;
    return min(find_min(tree, idx*2, tree_l, middle, l, min(r, middle)),
               find_min(tree, idx*2+1, middle+1, tree_r, max(l, middle+1), r));
}

void print_window(deque<pair<int, int>> window) {
    cout << "=== WINDOW ===" << endl;
    for (auto v: window) {
        cout << "[" << v.second << "] = " << v.first << endl;
    }
    cout << "==============" << endl;
}

void print_min(deque<pair<int, int>> window) {
    //assume window is sorted
    cout << window.begin()->first << " ";
}

bool delete_first(deque<pair<int, int>>& window, int cur, int k) {
    int first_idx = cur - k;
    for (deque<pair<int, int>>::iterator iter = window.begin(); iter != window.end(); iter++) {
        if (iter->second == first_idx) {
            window.erase(iter);
            return true;
        }
    }
    return false;
}

bool insert_new(deque<pair<int, int>>& window, int cur, int pos) {
    //cout << "[" << pos << "] := " << cur << endl;
    for (deque<pair<int, int>>::iterator iter = window.begin(); iter != window.end(); iter++) {
        if (iter->first >= cur) {
            window.insert(iter, make_pair(cur, pos));
            return true;
        }
    }
    window.push_back(make_pair(cur, pos));
    return true;
    return false;
}*/

int find_zero_pos_arr(array<int, 150000>& mins, int l, int r) {
    if (mins[l] == 0) {
        return l;
    }
    if (mins[r] == 0) {
        return r;
    }
    if (r - l <= 1) {
        return -1;
    }
    int middle = (l + r) / 2;
    int left_search = find_zero_pos_arr(mins, l, middle);
    if (left_search < 0) return find_zero_pos_arr(mins, middle, r);
    return left_search;
}

void naive_improved(int n, int k, vector<pair<int, int>>& values, array<int, 150000>& mins) {
    int windows_count = n - k + 1;
    for (auto it: values) {
        if (windows_count <= 0) break;
        int pos = it.second;
        int right_bound = calc_right_bound(pos, k, n);
        int left_bound = calc_left_bound(pos, k);
        int middle = find_zero_pos_arr(mins, left_bound, right_bound);
        if (middle >= 0) {
            for (int j = middle; j >= left_bound; j--) {
                if (mins[j] != 0) {
                    break;
                }
                mins[j] = it.first;
                windows_count--;
            }
            if (windows_count <= 0) break;
            for (int j = middle + 1; j <= right_bound; j++) {
                if (mins[j] != 0) {
                    break;
                }
                mins[j] = it.first;
                windows_count--;
            }
        }
    }

    //print_result(mins, n, k);
}

void naive(int n, int k, array<int, 150000>& entries, array<int, 150000>& mins) {
        for (int i = k - 1; i < n; i++) {
            int win_min = entries[i];
            for (int j = i - k + 1; j < i; j++) {
                if (entries[j] < win_min) {
                    win_min = entries[j];
                }
            }
            //cout << i << win_min << " ";
            mins[i] = win_min;
            //cout <<"h";
        }
    }

void stolen_for_testing(int n, int k, array<int, 150000>& entries, array<int, 150000>& mins) {
    list <pair<int, int>> segment;
    int j = k - 1;
    for (int i = 0; i < n; i++){
        if (!segment.empty() && i - segment.front().first >= k) segment.pop_front();
        int x = entries[i];
        while (!segment.empty() && segment.back().second > x) segment.pop_back();
        segment.push_back({i, x});
        if (i + 1 >= k)  {
            mins[j] = segment.front().second;
            j++;
        }
    }
}

void print_result_arr(array<int, 150000>& mins, int n, int k) {
    for (long long i = k - 1; i < n; i++) {
        cout << mins[i] << " ";
    }
    cout << endl;
}

int main() {
    //// stress test module
    int n, k;
    cin >> n >> k;
    //n = 100, k = 2;
    array<int, 150000> entries = {0};

    random_device dev;
    mt19937_64 rng(dev());
    uniform_int_distribution<std::mt19937_64::result_type> dist(-100000,100000);
    int test_count = 0;
    for (int i = 0; i < 10; i++) {
        vector<pair<int, int>> values;
        for (int i = 0; i < n; i++) {
            int cur = dist(rng);
            entries[i] = cur;
            values.push_back(make_pair(cur, i));
        }
        sort(values.begin(), values.end(), cmp);

        for (int k1 = k % 17 + 1; k1 < 7321; k1+= 1000) {
            array<int, 150000> arr1 = {0};
            stolen_for_testing(n, k1, entries, arr1);
            array<int, 150000> arr2 = {0};
            naive_improved(n, k1, values, arr2);
            if (!equal(arr1.begin(), arr1.end(), arr2.begin(), arr2.end())) {
                cout << "\n========\n";
                for (int i = 0; i < n; i++) {
                    cout << entries[i] << " ";
                }
                cout << endl;
                print_result_arr(arr1, n, k1);
                print_result_arr(arr2, n, k1);
                cout << "========\n\n";
            } else {
                cout << "|";
                test_count++;
            }
        }
    }
    cout << endl << test_count << " tests passed";



    /// очередь. tl 4

    /*
    int n, k;
    cin >> n >> k;
    deque<pair<int, int>> window;
    for (int i = 0; i < k; i++) {
        int cur;
        cin >> cur;
        window.push_back(make_pair(cur, i));
    }
    sort(window.begin(), window.end(), cmp);

    print_min(window);

    for (int i = k; i < n; i++) {
        int cur;
        cin >> cur;
        if (!delete_first(window, i, k)) {
            cerr << "Delete error";
            throw new exception;
        }
        if (!insert_new(window, cur, i)) {
            cerr << "Insert error";
            throw new exception;
        }
        //print_window(window);
        print_min(window);
    }*/

    /// naive algo for testing, tl 5

    /*
    int n, k;
    cin >> n >> k;
    int mins[150000] = {0};
    //map<int, deque<int>> values;
    vector<pair<int, int>> values;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        values.push_back(make_pair(cur, i));
    }
    sort(values.begin(), values.end(), cmp);
    int windows_count = n - k + 1;

    //print_vals_map(values);
    for (auto it: values) {
        if (windows_count <= 0) break;
        //print_result(mins, n, k);
        int pos = it.second;
        int right_bound = calc_right_bound(pos, k, n);
        int left_bound = calc_left_bound(pos, k);
        //cout << "[" << pos << "," << right_bound << "]\n";
        int middle = find_zero_pos(mins, left_bound, right_bound);
        if (middle >= 0) {
            for (int j = middle; j >= left_bound; j--) {
                if (mins[j] != 0) {
                    break;
                }
                mins[j] = it.first;
                windows_count--;
            }
            if (windows_count <= 0) break;
            for (int j = middle + 1; j <= right_bound; j++) {
                if (mins[j] != 0) {
                    break;
                }
                mins[j] = it.first;
                windows_count--;
            }
        }
        //print_result(mins, n, k);
    }

    print_result(mins, n, k);

*/


    /// segment tree, tl 3? why is it slower than naive algo....
    /*
    int n, k;
    cin >> n >> k;
    vector<int> tree;
    tree.resize(n * 4);
    int src_arr[150001];
    for (int i = 0; i < n; i++) {
        cin >> src_arr[i];
    }
    build_tree(tree, src_arr, 1, 0, n - 1);
    for (int left = 0; left <= n - k; left++) {
        int right = left + k - 1;
        cout << find_min(tree, 1, 0, n - 1, left, right) << " ";
    }*/
}
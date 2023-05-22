//
// Created by Женя on 21.04.2023.
//

#include <iostream>
#include <map>
#include <deque>
#include <vector>

using namespace std;

void erase_block_from_multimap(multimap<int, int>& offset_by_size, int offset, int size) {
    auto it = offset_by_size.find(size);
    while (it->second != offset) {
        it++;
    }
    if (it != offset_by_size.end()) {
        offset_by_size.erase(it);
    } // O(n)
}

void print_free(map<int, int>& size_by_offset) {
    cout << "=== FREE BLOCKS ===\n";
    for (auto it = size_by_offset.begin(); it != size_by_offset.end(); it++) {
        cout << "[" << it->first << ".." << it->first + it->second - 1 << "] ";
    }
    cout << endl;
}

void print_history(vector<pair<int, int>>& history) {
    cout << "=== HISTORY ===\n";
    for (auto it = history.begin(); it != history.end(); it++) {
        if (it->first > 0) {
            cout << "[" << it - history.begin() << "]" << it->first << "->" << it->second << " ";
        }
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    map<int, int> size_by_offset = map<int, int>();
    multimap<int, int> offset_by_size;
    vector<pair<int, int>> history = vector<pair<int, int>>(m + 1);
    int req;

    size_by_offset[1] = n;
    offset_by_size.insert(make_pair(n, 1));

    for (int i = 1; i <= m; i++) {
        cin >> req;
        if (req > 0) {
            auto it = offset_by_size.lower_bound(req);
            if (it != offset_by_size.end()) {
                int size = it->first;
                int offset = it->second;
                int size_remaining = size - req;
                if (size_remaining > 0) {
                    int offset_next = offset + req;
                    size_by_offset[offset_next] = size_remaining;
                    offset_by_size.insert(make_pair(size_remaining, offset_next));
                }
                history[i] = make_pair(offset, req);
                size_by_offset.erase(offset);
                offset_by_size.erase(it);

                cout << offset << endl;
            } else {
                cout << -1 << endl;
            }
        } else {
            req = -req;

            int offset = history[req].first;
            int size = history[req].second;

            if (offset > 0 && size > 0) {
                auto next_free = size_by_offset.lower_bound(offset);
                map<int, int>::iterator prev_free;
                if (next_free == size_by_offset.begin()) {
                    prev_free = size_by_offset.end();
                } else {
                    prev_free = prev(next_free);
                }
                if (prev_free != size_by_offset.end() && prev_free->first + prev_free->second == offset) {
                    offset = prev_free->first;
                    size = prev_free->second + size;
                    erase_block_from_multimap(offset_by_size, prev_free->first, prev_free->second);
                    size_by_offset.erase(prev_free);
                }
                if (next_free != size_by_offset.end() && offset + size == next_free->first) {
                    size += next_free->second;
                    erase_block_from_multimap(offset_by_size, next_free->first, next_free->second);
                    size_by_offset.erase(next_free);
                }
                size_by_offset[offset] = size;
                offset_by_size.insert(make_pair(size, offset));
            }
        }
        //print_free(size_by_offset);
        //print_history(history);
    }
}

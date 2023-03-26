//
// Created by Женя on 01.03.2023.
//

#include <iostream>
#include <queue>

using namespace std;

bool compare(const pair<int, deque<int>> a, const pair<int, deque<int>> b) {
    if (a.second.size() < 2) {
        return b.second.size() >= 2 ;
    }
    if (b.second.size() < 2) {
        return false;
    }
    return *(a.second.begin() + 1) > *(b.second.begin() + 1);
}

struct Compare {
    bool operator()(const pair<int, deque<int>>& lhs, const pair<int, deque<int>>& rhs) {
        return compare(lhs, rhs);
    }
};



int main() {
    priority_queue<pair<int, deque<int>>, vector<pair<int, deque<int>>, Compare>;

}
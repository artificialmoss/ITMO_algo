//
// Created by Женя on 22.04.2023.
//

#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

string leader(set<pair<unsigned long long, string>, greater<>>& cities) {
    auto i = cities.begin();
    auto j = cities.begin();
    j++;
    if (i->first != j->first) {
        return i->second;
    }
    return "";
}

int main() {
    int n;
    cin >> n;
    unordered_map<string, string> mill_last_city = unordered_map<string, string>();
    unordered_map<string, long long> mill_net_worth = unordered_map<string, long long>();
    unordered_map<string, long long> city_value = unordered_map<string, long long>();
    map<string, int> city_days = map<string, int>();
    set<pair<unsigned long long, string>, greater<>> s = set<pair<unsigned long long, string>, greater<>>();
    string millionaire, city;
    unsigned long long net_worth;
    for (int i = 0; i < n; i++) {
        cin >> millionaire >> city >> net_worth;
        mill_last_city[millionaire] = city;
        mill_net_worth[millionaire] = net_worth;
        auto it = city_value.find(city);
        if (it == city_value.end()) {
            city_value[city] = net_worth;
        } else {
            it->second += net_worth;
        }
    }

    for (auto it : city_value) {
        s.insert(make_pair(it.second, it.first));
    }

    int days, k;
    cin >> days >> k;

    string prev_richest_city = leader(s), cur_richest_city;
    int prev_day = 1, cur_day;
    string prev_city;

    for (int i = 0; i < k; i++) {
        cin >> cur_day >> millionaire >> city;
        cur_day++;
        prev_city = mill_last_city[millionaire];
        mill_last_city[millionaire] = city;
        s.erase(make_pair(city_value[city], city));
        s.erase(make_pair(city_value[prev_city], prev_city));
        city_value[city] += mill_net_worth[millionaire];
        city_value[prev_city] -= mill_net_worth[millionaire];
        s.insert(make_pair(city_value[city], city));
        s.insert(make_pair(city_value[prev_city], prev_city));
        if (!prev_richest_city.empty()) {
            auto it = city_days.find(prev_richest_city);
            if (it != city_days.end()) {
                it->second += cur_day - prev_day;
            } else {
                city_days[prev_richest_city] = cur_day - prev_day;
            }
        }
        prev_richest_city = leader(s);
        prev_day = cur_day;
    }
    cur_day = days + 1;

    if (!prev_richest_city.empty()) {
        auto it = city_days.find(prev_richest_city);
        if (it != city_days.end()) {
            it->second += cur_day - prev_day;
        } else {
            city_days[prev_richest_city] = cur_day - prev_day;
        }
    }

    for (auto it : city_days) {
        if (it.second != 0) {
            cout << it.first << " " << it.second << endl;
        }
    }

}
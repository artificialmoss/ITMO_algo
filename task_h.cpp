//
// Created by Женя on 09.02.2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    int n, k;
    cin >> n >> k;
    vector<int> values;
    values.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> values.at(i);
    }
    sort(values.begin(), values.end(), std::greater<int>());
    int sum = 0;
    for (int i = 0 ; i < n; i++) {
        if (i % k != k - 1) {
            sum += values.at(i);
        }
    }
    cout << sum << endl;
}
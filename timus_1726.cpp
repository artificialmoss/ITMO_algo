#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    long long n;
    cin >> n;
    vector<int> x_coords, y_coords;
    x_coords.resize(n);
    y_coords.resize(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> x_coords.at(i) >> y_coords.at(i);
    }
    sort(x_coords.begin(), x_coords.end());
    sort(y_coords.begin(), y_coords.end());
    long long c = 0;

    for (int i = 1; i < n; i++) {
        long long dist_x = x_coords.at(i) - x_coords.at(i - 1);
        long long dist_y = y_coords.at(i) - y_coords.at(i - 1);
        c += (n - 1 - 2*(i - 1));
        sum += (dist_x + dist_y) * c;
        /*for (int j = 1; j < n; j++) {
            int factor =  min(min(i, (int) n - i), min(j, (int) n - j));
            cout << i << " " << j << " " << factor << " -> ";
            sum += (dist_x + dist_y) * factor;
            cout << sum << endl;
        }*/
        // naive algo, test 10 TL
    }
    sum /= n * (n-1) / 2;

    cout << sum << endl;
}
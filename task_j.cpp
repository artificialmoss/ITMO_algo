#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

void stabilize_queue(int length, deque<int>& first, deque<int>& second) {
    if (length % 2 == 1) {
        int tmp = second.front();
        second.pop_front();
        first.push_back(tmp);
    }
}

int main() {
    deque<int> first_half;
    deque<int> second_half;
    int length = 0;
    string line;
    int number;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> line;
        switch(line[0]) {
            case '+' : {
                cin >> number;
                length++;
                second_half.push_back(number);
                break;
            }
            case '*': {
                cin >> number;
                second_half.push_front(number);
                length++;
                break;
            }
            case '-': {
                cout << first_half.front() << endl;
                first_half.pop_front();
                length--;
                break;
            }
        }
        stabilize_queue(length, first_half, second_half);
    }
}
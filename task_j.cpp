#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    deque<int> queue;
    deque<int>::iterator middle_position = queue.begin();
    int length = 0;
    string line;
    for (int i = 0; i < n; i++) {
        cin >> line;
        int goblin_number;
        if (length == 0) {
            middle_position = queue.begin();
        }
        switch (line.at(0)) {
            case '+': {
                cin >> goblin_number;
                queue.push_back(goblin_number);
                if (length == 0) {
                    middle_position = queue.begin();
                }
                length++;
                if (length % 2 == 1) {
                    middle_position++;
                }
                break;
            }
            case '*': {
                cin >> goblin_number;
                queue.insert(middle_position, goblin_number);
                if (length == 0) {
                    middle_position = queue.begin();
                }
                length++;
                if (length % 2 == 1) {
                    middle_position++;
                }
                break;
            }
            case '-': {
                cout << queue.front() << endl;
                length--;
                if (length % 2 == 1) {
                    middle_position++;
                }
                queue.pop_front();
                break;
            }
        }
    }
}
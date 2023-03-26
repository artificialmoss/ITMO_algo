#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

/*void print_deque(deque<int>& queue, const deque<int>::iterator& middle_pos) {
    for (auto it = queue.begin(); it != queue.end(); it++) {
        if (*it == *middle_pos) {
            cout << "[ ] " << *it << " ";
        } else {
            cout << *it << " ";
        }
    }
    if (*middle_pos == *queue.end()) {
        cout << "[ ] ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    deque<int> queue;
    auto middle_position = queue.begin();
    int length = 0;
    string line;
    for (int i = 0; i < n; i++) {
        cin >> line;
        int goblin_number;
        if (length == 0) {
            middle_position = queue.begin();
        }
        //print_deque(queue, middle_position);
        switch (line.at(0)) {
            case '+': {
                cin >> goblin_number;
                queue.push_back(goblin_number);
                length++;
                break;
            }
            case '*': {
                cin >> goblin_number;
                queue.insert(middle_position, goblin_number);
                length++;
                break;
            }
            case '-': {
                cout << queue.front() << endl;
                length--;
                queue.pop_front(); //проблема НЕ в этом
                break;
            }
        }

        if (length == 1) {
            middle_position = queue.end();
        }
        else {
            if (length % 2 == 1) {
                middle_position++;
            }
        }

        //cout << length << " " << (middle_position == queue.end()) << endl;
        print_deque(queue, middle_position);
    }
}*/

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
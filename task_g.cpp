//
// Created by Женя on 16.02.2023.
//

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

bool comp(pair<char,int> lx, pair<char,int> rx) {
    return lx.second > rx.second;
}

void print_weights(pair<char, int> weights[26]) {
    cout << "==== WEIGHTS ====" << endl;
    for (int i = 0; i < 26; i++) {
        cout << weights[i].first << " -> " << weights[i].second << endl;
    }
}

void print_counts(int char_counts[26]) {
    cout << "==== COUNTS ====" << endl;
    for (int i = 0; i < 26; i++) {
        cout << (char) (i + 'a') << " -> " << char_counts[i] << endl;
    }
}

void print_resulting_string(vector<char> vector) {
    for (int i = 0; i < vector.size(); i++) {
        cout << vector.at(i);
    }
    cout << endl;
}

int main() {
    pair<char, int> weights[26];
    string line;
    cin >> line;
    int char_counts[26] = {0};
    vector<char> resulting_string;
    resulting_string.resize(line.length());
    for (int i = 0; i < line.length(); i++) {
        char_counts[line.at(i) - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        weights[i] = make_pair(i + 'a', 0);
        cin >> weights[i].second;
    }
    sort(begin(weights), end(weights), comp);

    int begin = 0;
    int end = line.length() - 1;
    for (int i = 0; i < 26; i++) {
        if (char_counts[weights[i].first - 'a'] >= 2) {
            resulting_string.at(begin) = weights[i].first;
            resulting_string.at(end) = weights[i].first;
            char_counts[weights[i].first - 'a'] -= 2;
            begin++;
            end--;
        }
    }
    for (int i = 0; i < 26 && begin <= end; i++) {
        while (char_counts[i] > 0) {
            resulting_string.at(begin) = i + 'a';
            begin++;
            char_counts[i]--;
        }
    }

    print_resulting_string(resulting_string);
}

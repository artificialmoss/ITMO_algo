/// for Malika :)

#include <iostream>
#include <stack>
#include <unordered_map>
#include <list>

using namespace std;

bool isNumeric(std::string const &str){
    return str[0] == '-' || isdigit(str[0]);
}

int main() {
    unordered_map<string, stack<int>> values;
    stack<list<string>> variables;
    variables.push(list<string>());
    string in;
    while(cin >> in) {
        string a, b;
        if (in[0] == '{'){
            variables.push(list<string>());
        }
        else if (in[0] == '}'){
            for (auto it = variables.top().begin(); it != variables.top().end(); it++) {
                values[*it].pop();
                if (values[*it].empty()) {
                    values.erase(*it);
                }
            }
            if (variables.size() == 0) {
                variables.push(list<string>());
            } else {
                variables.pop();
            }
        }
        else {
            auto findEq = in.find('=');
            a = in.substr(0, findEq);
            b = in.substr(findEq + 1);
            int value;
            if (isNumeric(b)) {
                value = stoi(b);
            }
            else {
                auto findB = values.find(b);
                if (findB != values.end()) {
                    value = findB->second.top();
                } else {
                    value = 0;
                }
                cout << value << '\n';
            }
            auto findA = values.find(a);
            if (findA != values.end()) {
                findA->second.push(value);
            } else {
                values[a] = stack<int>();
                values[a].push(value);
            }
            variables.top().push_back(a);
        }
    }
}


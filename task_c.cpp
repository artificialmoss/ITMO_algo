//
// Created by Женя on 08.02.2023.
//

#include <iostream>
#include <deque>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

int main() {
    std::deque<std::deque<std::string>> variables;
    std::unordered_set<std::string> variable_list;
    std::unordered_map<std::string, std::stack<int>> values;
    std::string input_line, var1, var2;
    while (std::cin >> input_line) {
        switch (input_line.at(0)) {
            case '{' : {
                variables.push_back(std::deque<std::string>());
                break;
            }
            case '}' : {
                if (variables.size() > 0) {
                    if (variables.back().size() > 0) {
                        for (std::deque<std::string>::iterator iter = variables.back().begin();
                             iter != variables.back().end(); iter++) {
                            if (values.count(*iter) > 0) {
                                values[*iter].pop();
                                if (values[*iter].size() == 0) {
                                    variable_list.erase(*iter);
                                    values.erase(*iter);
                                }
                            } else {
                                values.erase(*iter);
                                variable_list.erase(*iter);
                            }
                        }
                    }
                    variables.pop_back();
                }
                break;
            }
            default: {
                int eq_pos = input_line.find('=');
                if (variables.size() == 0) {
                    variables.push_back(std::deque<std::string>());
                }
                var1 = input_line.substr(0, eq_pos);
                var2 = input_line.substr(eq_pos + 1, input_line.length() - eq_pos - 1);
                int value = 0;

                // get value + print if necessary

                if (isdigit(var2.at(0)) || var2.at(0) == '-') {
                    value = std::stoi(var2);
                } else {
                    std::unordered_set<std::string>::iterator iter = variable_list.find(var2);
                    if (iter != variable_list.end()) {
                        value = values[var2].top();
                    }
                    std::cout << value << std::endl;
                }

                // save value

                if (variable_list.find(var1) == variable_list.end()) {
                    variable_list.insert(var1);
                    variables.back().push_back(var1);
                    values[var1] = std::stack<int>();
                    values[var1].push(value);
                } else {
                    if (std::find(variables.back().begin(), variables.back().end(), var1) == variables.back().end()) {
                        values[var1].push(value);
                        variables.back().push_back(var1);
                    } else {
                        values[var1].pop();
                        values[var1].push(value);
                    }
                }
                break;
            }
        }
    }
}


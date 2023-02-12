#include <iostream>
#include <stack>
#include <vector>

int main(void) {
    std::string input;
    std::cin >> input;
    std::stack<std::pair<int, char>> stack;
    std::vector<int> order;
    int animal_id = 0;
    int trap_id = -1;
    int is_animal;
    int length = input.length();
    if (length % 2 != 0) {
        std::cout << "Impossible" << std::endl;
        return 0;
    }
    order.resize(length / 2);
    for (int i = 0; i < length; i++) {
        if (input.at(i) >= 'a' && input.at(i) <= 'z') {
            is_animal = 1;
            animal_id++;
        } else {
            is_animal = 0;
            trap_id++;
        }
        //std::cout << input.at(i) << " animal: " << animal_id << ", trap: " << trap_id <<std::endl;
        if (stack.size() != 0 && stack.top().second != input.at(i) && std::tolower(stack.top().second) == std::tolower(input.at(i))) {
            if (input.at(i) >= 'a') {
                // на стеке ловушка и её индекс
                order.at(stack.top().first) = animal_id;
            } else {
                // на стеке животное и его номер
                order.at(trap_id) = stack.top().first;
            };
            stack.pop();
        } else {
            stack.push(std::pair<int, char> (animal_id * is_animal + trap_id * (1 - is_animal), input.at(i)));
        }
    }

    if (stack.size() != 0) {
        std::cout << "Impossible" << std::endl;
        return 0;
    }

    std::cout << "Possible" << std::endl;
    for (auto i : order) {
        std::cout << i << " ";
    }
    for (int i = 0; i < length/2; i++) {
        //std::cout << order.at(i) << " ";
    }

}
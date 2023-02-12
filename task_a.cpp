#include <iostream>
#include <tuple>

int main(void) {
    std::tuple<int, int, int> triple;
    std::get<0>(triple) = 0;
    std::get<1>(triple) = 0;
    std::get<2>(triple) = 0;
    int n, cur;
    int max_length = 0, cur_length = 0, idx = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> cur;
        std::get<0>(triple) = cur;

        if (cur == std::get<1>(triple) && cur == std::get<2>(triple)) {
            if (cur_length > max_length) {
                max_length = cur_length;
                idx = i - max_length;
            }
            cur_length = 2;
        } else {
            cur_length++;
        }
        std::swap(std::get<1>(triple), std::get<2>(triple));
        std::swap(std::get<0>(triple), std::get<1>(triple));
    }
    if (cur_length > max_length) {
        max_length = cur_length;
        idx = n - max_length + 1;
    }

    std::cout << idx << " " << max_length + idx - 1<< std::endl;
}
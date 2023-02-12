#include <iostream>

int main(void) {
    int m;
    int fighters, group_count;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> fighters >> group_count;
        int group_size_min = fighters / group_count;
        int full_group_count = fighters % group_count;
        int remaining_groups = group_count - full_group_count;
        int sum = ((group_size_min + 1) * (group_size_min + 1) * full_group_count * (full_group_count - 1) +
                (group_size_min)*group_size_min*remaining_groups*(remaining_groups - 1))/2 +
                group_size_min*(group_size_min + 1)*full_group_count * remaining_groups;
        std::cout << sum << std::endl;
    }
    return 0;
}

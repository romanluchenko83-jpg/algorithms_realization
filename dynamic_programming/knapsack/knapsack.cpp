// Branch created and file with 0-1 knapsack algorithm added
// Note: Need to fix VLA (variable-length array) — VLAs are non-standard in C++ and can cause stack overflow. Consider using std::vector or a 1D DP optimization.

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

namespace Knapsack_problem {
    struct Items {
        std::vector<unsigned int> weights_of_items;
        std::vector<unsigned int> values_of_items;
        Items(std::initializer_list<std::pair<unsigned int, unsigned int>> items) {
            for (const auto& item : items) {
                weights_of_items.push_back(item.first);
                values_of_items.push_back(item.second);
            }
        }
        ~Items() = default;
    };

    unsigned int solve_knapsack_dp(const Items& items, unsigned int max_weight);
}

int main() {
    Knapsack_problem::Items concrete_items{{4, 10}, {3, 7}, {3, 7}};
    Knapsack_problem::Items concrete_items1{{5, 3}, {10, 5}, {6, 4}, {5, 2}};

    std::cout << Knapsack_problem::solve_knapsack_dp(concrete_items, 6) << std::endl;
    std::cout << Knapsack_problem::solve_knapsack_dp(concrete_items1, 14) << std::endl;

    return 0;
}

unsigned int Knapsack_problem::solve_knapsack_dp(const Items& items, unsigned int max_weight) {
    unsigned int count_elems = items.weights_of_items.size();
    unsigned int dynamic_knapsack[count_elems + 1][max_weight + 1];

    for (unsigned int weight = 0; weight <= max_weight; weight++) {
        dynamic_knapsack[0][weight] = 0;
    }

    for (unsigned int item_count = 1; item_count <= count_elems; item_count++) {
        for (unsigned int weight = 0; weight <= max_weight; weight++) {
            unsigned int current_weight = items.weights_of_items.at(item_count - 1);
            unsigned int current_value = items.values_of_items.at(item_count - 1);

            if (current_weight > weight) {
                dynamic_knapsack[item_count][weight] = dynamic_knapsack[item_count - 1][weight];
            } else {
                dynamic_knapsack[item_count][weight] = std::max(dynamic_knapsack[item_count - 1][weight],
                    dynamic_knapsack[item_count - 1][weight - current_weight] + current_value);
            }
        }
    }

    return dynamic_knapsack[count_elems][max_weight];
}

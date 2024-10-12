#ifndef BENCHMARKER_HPP
#define BENCHMARKER_HPP

#include <chrono>
#include <iostream>
#include <vector>

struct benchmarker_t {
    // Solution info
    int32_t constructive_heuristic_avg_cost;
    int32_t post_rvnd_avg_cost;
    int32_t final_solution_avg_cost;

    std::vector<size_t> best_solution_sequence;
    int32_t best_solution_cost;

    // Time tracking info
    std::chrono::duration<double> avg_elapsed_time;

    // Member function to calculate the gap
    double CalculateGap(int32_t optimal_value) {
        if (optimal_value == 0) return 0.0; // Avoid division by zero
        return static_cast<double>((final_solution_avg_cost - optimal_value) / optimal_value) * 100.0;
    }

    // Print benchmark results
    void printResults(std::string instance_name, int32_t optimal_value) {
        std::cout << "Instance: " << instance_name << '\n';
        std::cout << "Optimal Cost: " << optimal_value << '\n';
        std::cout << "Constructive Heuristic Avg Cost: " << constructive_heuristic_avg_cost << '\n';
        std::cout << "Post-RVND Avg Cost: " << post_rvnd_avg_cost << '\n';
        std::cout << "Final Solution Avg Cost: " << final_solution_avg_cost << '\n';
        std::cout << "Average Elapsed Time: " << avg_elapsed_time.count() << " s" << '\n';
        std::cout << "GAP: " << CalculateGap(optimal_value) << '\n';
        std::cout << "============================================================================\n";
        std::cout << "Best Solution Sequence: ";

        for (size_t element : best_solution_sequence) {
            std::cout << element << ", ";
        }

        std::cout << '\n';
        std::cout << "Best Solution Cost: " << best_solution_cost << '\n';
        std::cout << "============================================================================\n";
    }
};

#endif
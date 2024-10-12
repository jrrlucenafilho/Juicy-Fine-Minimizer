#ifndef BENCHMARKER_HPP
#define BENCHMARKER_HPP

#include <chrono>
#include <iostream>
#include <vector>

struct benchmarker_t {
    // Solution info
    int32_t constructive_heuristic_avg_cost = 0;
    int32_t rvnd_avg_cost = 0;
    int32_t metaheuristic_solution_avg_cost = 0;

    std::vector<size_t> best_solution_sequence;
    int32_t best_solution_cost;

    // Time tracking info
    std::chrono::duration<double> constructive_heuristic_avg_elapsed_time;
    std::chrono::duration<double> rvnd_avg_elapsed_time;
    std::chrono::duration<double> metaheuristic_avg_elapsed_time;

    // Member function to calculate the gap
    double CalculateGap(int32_t input_cost, int32_t optimal_cost) {
        if (optimal_cost == 0) return 0.0; // Avoid division by zero
        return static_cast<double>((input_cost - optimal_cost) / optimal_cost) * 100.0;
    }

    // Print benchmark results
    void printResults(std::string instance_name, int32_t optimal_cost) {
        std::cout << "Instance: " << instance_name << '\n';
        std::cout << "Optimal Cost: " << optimal_cost << '\n';
        std::cout << "--------------------------Constructive Heuristic-----------------------------\n";
        std::cout << "Constructive Heuristic Avg Cost: " << constructive_heuristic_avg_cost << '\n';
        std::cout << "Constructive Heuristic Avg Time: " << constructive_heuristic_avg_elapsed_time.count() << '\n';
        std::cout << "Constructive Heuristic GAP" << CalculateGap(constructive_heuristic_avg_cost, optimal_cost) << '\n';
        std::cout << "----------------------------------RVND---------------------------------------\n";
        std::cout << "RVND Avg Cost: " << rvnd_avg_cost << '\n';
        std::cout << "RVND Avg Time: " << rvnd_avg_elapsed_time.count() << '\n';
        std::cout << "RVND GAP: " << CalculateGap(rvnd_avg_cost, optimal_cost);
        std::cout << "-----------------------------Metaheuristic-----------------------------------\n";
        std::cout << "Metaheuristic Avg Cost: " << metaheuristic_solution_avg_cost << '\n';
        std::cout << "Metahueristic Avg Time: " << metaheuristic_avg_elapsed_time.count() << " s" << '\n';
        std::cout << "Metaheuristic GAP: " << CalculateGap(metaheuristic_solution_avg_cost, optimal_cost) << '\n';
        std::cout << "--------------------------Best Solution Found--------------------------------\n";
        std::cout << "Best Solution Cost: " << best_solution_cost << '\n';
        std::cout << "Best Solution Sequence: ";

        for (size_t element : best_solution_sequence) {
            std::cout << element << ", ";
        }

        std::cout << '\n';
    }
};

#endif
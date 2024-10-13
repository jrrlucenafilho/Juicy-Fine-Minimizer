#ifndef BENCHMARKER_HPP
#define BENCHMARKER_HPP

#include <chrono>
#include <iostream>
#include <vector>

struct benchmarker_t {
    // Solution info (will act as a sum and then be divided by 10 on print)
    float constructive_heuristic_avg_cost = 0;
    float rvnd_avg_cost = 0;
    float metaheuristic_solution_avg_cost = 0;

    int32_t best_solution_iter;

    std::vector<size_t> best_solution_sequence;
    int32_t best_solution_cost;

    // Time tracking info
    std::chrono::duration<double> constructive_heuristic_avg_elapsed_time{0.0};
    std::chrono::duration<double> rvnd_avg_elapsed_time{0.0};
    std::chrono::duration<double> metaheuristic_avg_elapsed_time{0.0};

    // Utils for time tracking
    // Constr heuristic time
    std::chrono::time_point<std::chrono::high_resolution_clock> constr_heuristic_start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> constr_heuristic_end_time;

     // RVND time
    std::chrono::time_point<std::chrono::high_resolution_clock> rvnd_start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> rvnd_end_time;

     // Metaheuristic time
    std::chrono::time_point<std::chrono::high_resolution_clock> metaheuristic_start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> metaheuristic_end_time;

    // Member function to calculate the gap
    double CalculateGap(int32_t input_cost, int32_t optimal_cost) {
        if (optimal_cost == 0) return 0.0; // Avoid division by zero
        return ((double)(input_cost - optimal_cost) / optimal_cost) * 100.0;
    }

    // Print benchmark results
    void printResults(std::string instance_name, int32_t optimal_cost) {
        // Firstly divide avgs by 10, as they are just sums up to now
        constructive_heuristic_avg_cost /= 10;
        rvnd_avg_cost /= 10;
        metaheuristic_solution_avg_cost /= 10;

        constructive_heuristic_avg_elapsed_time /= 10;
        rvnd_avg_elapsed_time /= 10;
        metaheuristic_avg_elapsed_time /= 10;
        std::cout << "==================================Results====================================\n";
        std::cout << "Instance: " << instance_name << '\n';
        std::cout << "Optimal Cost: " << optimal_cost << '\n';
        std::cout << "--------------------------Constructive Heuristic-----------------------------\n";
        std::cout << "Constructive Heuristic Avg Cost: " << constructive_heuristic_avg_cost << '\n';
        std::cout << "Constructive Heuristic Avg Time: " << constructive_heuristic_avg_elapsed_time.count() << " s \n";
        std::cout << "Constructive Heuristic GAP: " << CalculateGap(constructive_heuristic_avg_cost, optimal_cost) << " %\n";
        std::cout << "----------------------------------RVND---------------------------------------\n";
        std::cout << "RVND Avg Cost: " << rvnd_avg_cost << '\n';
        std::cout << "RVND Avg Time: " << rvnd_avg_elapsed_time.count() << " s \n";
        std::cout << "RVND GAP: " << CalculateGap(rvnd_avg_cost, optimal_cost) << " %\n";
        std::cout << "-----------------------------Metaheuristic-----------------------------------\n";
        std::cout << "Metaheuristic Avg Cost: " << metaheuristic_solution_avg_cost << '\n';
        std::cout << "Metaheuristic Avg Time: " << metaheuristic_avg_elapsed_time.count() << " s \n";
        std::cout << "Metaheuristic GAP: " << CalculateGap(metaheuristic_solution_avg_cost, optimal_cost) << " %\n";
        std::cout << "--------------------------Best Solution Found--------------------------------\n";
        std::cout << "Best Solution Cost: " << best_solution_cost << '\n';
        std::cout << "Best Solution Iteration: " << best_solution_iter << '\n';
        std::cout << "Best Solution Sequence: ";

        for (size_t i = 0; i < best_solution_sequence.size(); i++) {
            std::cout << best_solution_sequence[i];

            if (i != best_solution_sequence.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
};

#endif
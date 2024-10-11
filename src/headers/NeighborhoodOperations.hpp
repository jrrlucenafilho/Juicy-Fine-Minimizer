#ifndef NEIGHBORHOODOPERATIONS_HPP
#define NEIGHBORHOODOPERATIONS_HPP

#include "Instance.hpp"
#include "Solution.hpp"

enum NeighborhoodStructure { SWAP, TWO_OPT, OR_OPT };

bool BestImprovementSwap(Instance &instance, Solution &curr_solution);

bool BestImprovementOrOpt(Instance &instance, Solution &curr_solution);

bool BestImprovement2Opt(Instance &instance, Solution &solution);

void LocalSearchRVND(Instance &instance, Solution &curr_solution);

Solution Disturbance(Instance &instance, Solution &solution);

Solution IteratedLocalSearch(int max_iters, int max_iters_ILS,
                             Instance &instance);
#endif

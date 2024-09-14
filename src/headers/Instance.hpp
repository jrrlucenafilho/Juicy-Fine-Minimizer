/**
 * @file Instance.hpp
 * @brief Definition of the Instance class.
 */

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <cmath>
#include <cstdint>
#include <exception>
#include <string>
#include <vector>

/**
 * @class InstanceNotFoundException
 * @brief Exception thrown when an instance is not found.
 */
class InstanceNotFoundException : public std::exception {
public:
  /**
   * @brief Get the description of the exception.
   *
   * @return The description of the exception.
   */
  const char *what();
};

/**
 * @class Instance
 * @brief Represents an instance with production times, delivery time limits,
 *        late fees, and transition times.
 */
class Instance {
public:
  /**
   * @brief Constructs an instance from a file path.
   *
   * @param instance_filepath The path to the instance file.
   */
  Instance(std::string instance_filepath);

  /**
   * @brief Returns the number of requests in the instance.
   *
   * @return The quantity of requests.
   */
  size_t getQuantityOfRequests();

  /**
   * @brief Returns the production time for a request at the given index.
   *
   * @param index The index of the request.
   *
   * @return The production time.
   */
  uint16_t getProductionTime(size_t index);

  /**
   * @brief Returns the delivery time limit for a request at the given index.
   *
   * @param index The index of the request.
   *
   * @return The delivery time limit.
   */
  uint16_t getDeliveryTimeLimit(size_t index);

  /**
   * @brief Returns the late fee for a request at the given index.
   *
   * @param index The index of the request.
   *
   * @return The late fee.
   */
  float_t getLateFee(size_t index);

  /**
   * @brief Returns the transition time between two requests.
   *
   * @param from The index of the first request.
   * @param to The index of the second request.
   *
   * @return The transition time.
   */
  uint16_t getTransitionTime(size_t from, size_t to);

  /**
   * @brief Returns whether the instance has been loaded.
   *
   * @return True if the instance is loaded, false otherwise.
   */
  bool isInstanceLoaded();

private:
  size_t quantity_of_requests;
  std::vector<uint16_t> production_times;
  std::vector<uint16_t> delivery_time_limits;
  std::vector<uint16_t> late_fees;
  std::vector<std::vector<uint16_t>> transition_times;
  bool instance_loaded;
}; // namespace Instance

#endif

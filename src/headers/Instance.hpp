#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <cmath>
#include <cstdint>
#include <exception>
#include <string>
#include <vector>

class InstanceNotFoundException : public std::exception {
public:
  const char *what();
};

class Instance {
public:
  Instance(std::string instance_filepath);

  size_t getQuantityOfRequests();

  uint16_t getProductionTime(size_t index);

  uint16_t getDeliveryTimeLimit(size_t index);

  float_t getLateFee(size_t index);

  uint16_t getTransitionTime(size_t from, size_t to);

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

#include "Instance.hpp"

#include <fstream>
#include <sstream>
#include <vector>

const char *InstanceNotFoundException::what() { return "Instance not found"; }

Instance::Instance(std::string instance_filepath) {
  std::ifstream instance_file(instance_filepath);
  std::string line;
  uint32_t line_number = 1;
  this->quantity_of_requests = 0;
  this->instance_loaded = false;

  if (!instance_file.is_open()) {
    throw InstanceNotFoundException();
  }

  while (std::getline(instance_file, line)) {
    std::istringstream iss(line);

    // // Get the number of requests from the first line
    if (line_number == 1) {
      iss >> this->quantity_of_requests;

      // Reserve the number of elements, that way the memory will not be moved
      this->production_times.reserve(this->quantity_of_requests);
      this->delivery_time_limits.reserve(this->quantity_of_requests);
      this->late_fees.reserve(this->quantity_of_requests);
    }

    if (line_number == 3) {
      for (int i = 0; i < this->quantity_of_requests; i++) {
        iss >> this->production_times[i];
      }
    }

    if (line_number == 4) {
      for (int i = 0; i < this->quantity_of_requests; i++) {
        iss >> this->delivery_time_limits[i];
      }
    }

    if (line_number == 5) {
      for (int i = 0; i < this->quantity_of_requests; i++) {
        iss >> this->late_fees[i];
        late_fees[i] /= 100.0;
      }
    }

    if (line_number >= 7) {
      uint16_t current_value;
      std::vector<uint16_t> current_matrix_line;

      for (int i = 0; i < this->quantity_of_requests; i++) {
        iss >> current_value;
        current_matrix_line.push_back(current_value);
      }

      this->transition_times.push_back(current_matrix_line);
    }

    line_number++;
  }

  instance_file.close();

  this->instance_loaded = true;
}

size_t Instance::getQuantityOfRequests() { return this->quantity_of_requests; }

uint16_t Instance::getProductionTime(size_t index) {
  return this->production_times[index];
}

uint16_t Instance::getDeliveryTimeLimit(size_t index) {
  return this->delivery_time_limits[index];
}

float_t Instance::getLateFee(size_t index) { return this->late_fees[index]; }

uint16_t Instance::getTransitionTime(size_t from, size_t to) {
  return this->transition_times[from][to];
}

bool Instance::isInstanceLoaded() { return this->instance_loaded; }

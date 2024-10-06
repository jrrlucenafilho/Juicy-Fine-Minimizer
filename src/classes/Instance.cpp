#include "Instance.hpp"

#include <fstream>
#include <sstream>
#include <vector>

const char *InstanceNotFoundException::what() { return "Instance not found"; }

Instance::Instance(std::string instance_filepath) {
  std::ifstream instance_file(instance_filepath);

  // Check if the file is open
  if (!instance_file.is_open()) {
    throw InstanceNotFoundException();
  }

  // Store each line of the file in a vector
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(instance_file, line)) {
    lines.push_back(line);
  }
  instance_file.close();

  // Initialize member variables using values from the first line
  this->quantity_of_requests = std::stoi(lines[0]);

  // Reserve space for vectors based on the quantity of requests
  this->production_times.reserve(this->quantity_of_requests);
  this->delivery_time_limits.reserve(this->quantity_of_requests);
  this->late_fees.reserve(this->quantity_of_requests);

  // Populate instance vectors

  /**
   * Using this strategy we only need to pass through all the three vectors once
   * So instead of being 3n it becomes n to load all vectors, not a big change for small values
   * But quite big for bigger values (e. g. if n = 100, 3n = 300 and n = 100)
   */
  std::istringstream iss[3] = {std::istringstream(lines[2]),
                               std::istringstream(lines[3]),
                               std::istringstream(lines[4])};
  uint16_t values[3];
  for (uint32_t j = 0; j < this->quantity_of_requests; ++j) {
    iss[0] >> values[0];
    iss[1] >> values[1];
    iss[2] >> values[2];

    // Assign the read value to the appropriate vector
    this->production_times.push_back(values[0]);
    this->delivery_time_limits.push_back(values[1]);
    this->late_fees.push_back(values[2]);
  }

  // Populate transition times matrix
  for (size_t i = 6; i < lines.size(); ++i) {
    std::istringstream iss(lines[i]);
    std::vector<uint16_t> current_matrix_line;

    // Read values and store them in the current row of the matrix
    for (uint32_t j = 0; j < this->quantity_of_requests; ++j) {
      uint16_t value;
      iss >> value;
      current_matrix_line.push_back(value);
    }

    // Add the row to the transition times vector
    this->transition_times.push_back(current_matrix_line);
  }

  // Set a flag indicating that the instance has been loaded successfully
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

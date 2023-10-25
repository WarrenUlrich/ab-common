#pragma once

#include <unordered_map>
#include <string>

#include "equipment_set.hpp"

namespace ab {
  class gear_manager {
  public:
    std::unordered_map<std::string, equipment_set> switches;
  };
}
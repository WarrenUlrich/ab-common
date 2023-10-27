#pragma once

#include <unordered_map>
#include <string>

#include "equipment_set.hpp"

namespace ab {
  class equipment_manager {
  public:
    std::unordered_map<std::string, equipment_set> switches;

    equipment_manager();
    ~equipment_manager();

    equipment_manager(const equipment_manager &other);
    equipment_manager(equipment_manager &&other);

    equipment_manager &operator=(const equipment_manager &other);
    equipment_manager &operator=(equipment_manager &&other);

    bool has(const std::string &switch_name) const;
    
    bool withdraw(const std::string &switch_name) const;
    
    bool equipped(const std::string &switch_name) const;

    bool equip(const std::string &switch_name) const;
  };
}
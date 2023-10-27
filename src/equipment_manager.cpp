#include <ab/equipment_manager.hpp>

namespace ab {
equipment_manager::equipment_manager() = default;
equipment_manager::~equipment_manager() = default;

equipment_manager::equipment_manager(
    const equipment_manager &other)
    : switches(other.switches) {}

equipment_manager::equipment_manager(
    equipment_manager &&other)
    : switches(std::move(other.switches)) {}

equipment_manager &equipment_manager::operator=(
    const equipment_manager &other) {
  if (this != &other) {
    switches = other.switches;
  }

  return *this;
}
equipment_manager &
equipment_manager::operator=(equipment_manager &&other) {
  if (this != &other) {
    switches = std::move(other.switches);
  }

  return *this;
}

bool equipment_manager::has(
    const std::string &switch_name) const {
  return switches.at(switch_name).has();
}

bool equipment_manager::withdraw(
    const std::string &switch_name) const {
  return switches.at(switch_name).withdraw();
}

bool equipment_manager::equipped(
    const std::string &switch_name) const {
  const auto &set = switches.at(switch_name);
  return switches.at(switch_name).equipped();
}

bool equipment_manager::equip(
    const std::string &switch_name) const {
  const auto &set = switches.at(switch_name);
  return set.equip();
}
} // namespace ab
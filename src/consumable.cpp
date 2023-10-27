#include <ab/consumable.hpp>

#include <Game/Core.hpp>

namespace ab {
consumable::consumable() = default;

consumable::~consumable() = default;

consumable::consumable(const consumable &other)
    : name_pattern(other.name_pattern) {}

consumable::consumable(consumable &&other)
    : name_pattern(std::move(other.name_pattern)) {}

consumable::consumable(std::string_view name_pattern)
    : name_pattern(name_pattern.begin(),
                   name_pattern.end()) {}

bool consumable::has() const {
  return Inventory::Contains(name_pattern);
}
} // namespace ab
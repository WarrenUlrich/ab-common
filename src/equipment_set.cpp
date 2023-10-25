#include <ab/equipment_set.hpp>

namespace ab {

// Default constructor
equipment_set::equipment_set() = default;

// Destructor
equipment_set::~equipment_set() = default;

// Copy constructor
equipment_set::equipment_set(const equipment_set &other) {
  // Deep copy of unique_ptr for each equippable item
  for (size_t i = 0; i < other._set.size(); ++i) {
    if (other._set[i]) {
      _set[i] = std::make_unique<equippable>(
          *(other._set[i].value().get()));
    }
  }
}

// Move constructor
equipment_set::equipment_set(
    equipment_set &&other) noexcept = default;

// Copy assignment operator
equipment_set &
equipment_set::operator=(const equipment_set &other) {
  if (this != &other) {
    equipment_set temp(other);
    std::swap(_set, temp._set);
  }
  return *this;
}

// Move assignment operator
equipment_set &equipment_set::operator=(
    equipment_set &&other) noexcept = default;

bool equipment_set::has(Equipment::SLOT slot) const {
  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];
  if (!equippable.has_value())
    return true;

  return equippable.value()->has();
}

// Check if all required items are present
bool equipment_set::has() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->has(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

// Equip an item in a specific slot
bool equipment_set::equip(Equipment::SLOT slot) const {
  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];
  if (!equippable.has_value())
    return true;

  return equippable.value()->equip();
}

// Equip all items
bool equipment_set::equip() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->equip(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

// Check if an item in a specific slot is equipped
bool equipment_set::equipped(Equipment::SLOT slot) const {
  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];
  if (!equippable.has_value())
    return true;

  return equippable.value()->equipped();
}

// Check if all items are equipped
bool equipment_set::equipped() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->equipped(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

// Access operator for non-const objects
std::optional<std::unique_ptr<equippable>> &
equipment_set::operator[](Equipment::SLOT slot) {
  return _set[static_cast<size_t>(slot)];
}

// Access operator for const objects
const std::optional<std::unique_ptr<equippable>> &
equipment_set::operator[](Equipment::SLOT slot) const {
  return _set[static_cast<size_t>(slot)];
}

// Equality operator
bool equipment_set::operator==(
    const equipment_set &other) const {
  return _set == other._set;
}

// Inequality operator
bool equipment_set::operator!=(
    const equipment_set &other) const {
  return !(*this == other);
}

} // namespace ab

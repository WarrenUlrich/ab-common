#include <ab/equipment_set.hpp>

namespace ab {

equipment_set::equipment_set() : _set({}) {}

equipment_set::~equipment_set() = default;

equipment_set::equipment_set(const equipment_set &other) {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    _set[slot] = other._set[slot];
  }
}

equipment_set::equipment_set(
    equipment_set &&other) noexcept = default;

equipment_set &
equipment_set::operator=(const equipment_set &other) {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    _set[slot] = other._set[slot];
  }

  return *this;
}

equipment_set &equipment_set::operator=(
    equipment_set &&other) noexcept = default;

void equipment_set::emplace(std::string_view name_pattern,
                            Equipment::SLOT slot) {
  _set[static_cast<std::size_t>(slot)] =
      equippable(name_pattern, slot);
}

bool equipment_set::has(Equipment::SLOT slot) const {
  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];
  if (!equippable.has_value())
    return true;

  return equippable->has();
}

bool equipment_set::has() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->has(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

bool equipment_set::equip(Equipment::SLOT slot) const {
  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];
  if (!equippable.has_value())
    return true;

  return equippable->equip();
}

bool equipment_set::equip() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->equip(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

bool equipment_set::equipped(Equipment::SLOT slot) const {
  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];
  if (!equippable.has_value())
    return true;

  return equippable->equipped();
}

bool equipment_set::equipped() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->equipped(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

bool equipment_set::in_bank(Equipment::SLOT slot) const {
  if (!Bank::IsOpen())
    return false;

  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];

  if (!equippable.has_value())
    return false;

  const auto banked_item =
      Bank::GetItem(equippable->name_pattern);
  if (!banked_item || banked_item.GetStackAmount() == 0)
    return false;

  return true;
}

bool equipment_set::withdraw(Equipment::SLOT slot) const {
  if (!Bank::IsOpen())
    return false;

  const auto &equippable =
      _set[static_cast<std::size_t>(slot)];

  if (!equippable.has_value())
    return false;

  const auto banked_item =
      Bank::GetItem(equippable->name_pattern);
  if (!banked_item || banked_item.GetStackAmount() == 0)
    return false;

  return Bank::Withdraw(banked_item, 1, true);
}

bool equipment_set::withdraw() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->withdraw(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

bool equipment_set::withdraw_missing() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (this->has(static_cast<Equipment::SLOT>(slot)))
      continue;

    if (!this->withdraw(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

bool equipment_set::in_bank() const {
  for (auto slot =
           static_cast<std::size_t>(Equipment::HEAD);
       slot < Equipment::AMMO; ++slot) {
    if (!this->in_bank(static_cast<Equipment::SLOT>(slot)))
      return false;
  }

  return true;
}

std::optional<equippable> &
equipment_set::operator[](Equipment::SLOT slot) {
  return _set[static_cast<size_t>(slot)];
}

const std::optional<equippable> &
equipment_set::operator[](Equipment::SLOT slot) const {
  return _set[static_cast<size_t>(slot)];
}

// // Equality operator
// bool equipment_set::operator==(
//     const equipment_set &other) const {
//   return _set == other._set;
// }

// // Inequality operator
// bool equipment_set::operator!=(
//     const equipment_set &other) const {
//   return !(*this == other);
// }

} // namespace ab

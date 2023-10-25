#pragma once

#include <memory>
#include <optional>

#include "equippable.hpp"

namespace ab {
class equipment_set {
public:
  equipment_set();

  ~equipment_set();

  bool has(Equipment::SLOT slot) const;
  bool has() const;

  bool equip(Equipment::SLOT slot) const;
  bool equip() const;

  bool equipped(Equipment::SLOT slot) const;
  bool equipped() const;

  equipment_set(const equipment_set &other);
  equipment_set(equipment_set &&other) noexcept;
  equipment_set &operator=(const equipment_set &other);
  equipment_set &operator=(equipment_set &&other) noexcept;

  std::optional<equippable> &
  operator[](Equipment::SLOT slot);
  const std::optional<equippable> &
  operator[](Equipment::SLOT slot) const;

  // bool operator==(const equipment_set &other) const;
  // bool operator!=(const equipment_set &other) const;

private:
  std::array<std::optional<equippable>, 11> _set;
};
} // namespace ab
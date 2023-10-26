#pragma once

#include <memory>
#include <optional>

#include "equippable.hpp"

namespace ab {
class equipment_set {
public:
  equipment_set();

  ~equipment_set();

  void emplace(std::string_view name_pattern, Equipment::SLOT slot);

  bool has(Equipment::SLOT slot) const;
  bool has() const;

  bool equip(Equipment::SLOT slot) const;
  bool equip() const;

  bool equipped(Equipment::SLOT slot) const;
  bool equipped() const;

  bool in_bank(Equipment::SLOT slot) const;
  bool in_bank();
  
  equipment_set(const equipment_set &other);
  equipment_set(equipment_set &&other) noexcept;
  equipment_set &operator=(const equipment_set &other);
  equipment_set &operator=(equipment_set &&other) noexcept;

  std::optional<equippable> &
  operator[](Equipment::SLOT slot);
  const std::optional<equippable> &
  operator[](Equipment::SLOT slot) const;

  auto begin() { return _set.begin(); }
  auto end() { return _set.end(); }

  auto begin() const { return _set.begin(); }
  auto end() const { return _set.end(); }

  auto cbegin() const { return _set.cbegin(); }
  auto cend() const { return _set.cend(); }

private:
  std::array<std::optional<equippable>, 11> _set;
};
} // namespace ab
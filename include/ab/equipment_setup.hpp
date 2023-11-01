#pragma once

#include <array>
#include <concepts>
#include <cstdint>
#include <optional>
#include <regex>
#include <string>

#include <Game/Core.hpp>

namespace ab {
template <typename ItemIdentifier>
  requires std::same_as<std::int32_t, ItemIdentifier> ||
           std::same_as<std::string, ItemIdentifier> ||
           std::same_as<std::regex, ItemIdentifier>
class equipment_setup {
public:
  equipment_setup() = default;
  ~equipment_setup() = default;

  void set_item(Equipment::SLOT slot, ItemIdentifier item_id) {
    _get(slot) = item_id;
  }

  bool in_inventory(Equipment::SLOT slot) const {
    const auto& item_id = _get(slot);
    if (!item_id.has_value())
      return false;
    
    return Inventory::Contains(item_id.value());
  }

  bool in_inventory() const {
    for (std::int32_t idx = Equipment::HEAD;
         idx < Equipment::AMMO; idx++) {
      const auto slot = static_cast<Equipment::SLOT>(idx);
      if (!in_inventory(slot))
        return false;
    }

    return true;
  }

  bool is_equipped(Equipment::SLOT slot) const {
    const auto &item_id = _get(slot);
    if (!item_id.has_value())
      return true;

    const auto item = Equipment::GetItem(slot);
    if (!item)
      return false;

    if constexpr (std::is_same_v<std::int32_t,
                                 ItemIdentifier>) {
      if (item.GetID() != item_id.value())
        return false;
    } else if constexpr (std::is_same_v<std::string,
                                        ItemIdentifier>) {
      if (item.GetName() != item_id.value())
        return false;
    } else if constexpr (std::is_same_v<std::regex,
                                        ItemIdentifier>) {
      if (!std::regex_match(item.GetName(), item_id))
        return false;
    }
    return true;
  }

  bool is_equipped() const {
    for (std::int32_t idx = Equipment::HEAD;
         idx < Equipment::AMMO; idx++) {
      const auto slot = static_cast<Equipment::SLOT>(idx);
      if (!is_equipped(slot))
        return false;
    }

    return true;
  }

  bool has(Equipment::SLOT slot) const {
    return in_inventory(slot) || is_equipped(slot);
  }

  bool has() const {
    for (std::int32_t idx = Equipment::HEAD;
         idx < Equipment::AMMO; idx++) {
      const auto slot = static_cast<Equipment::SLOT>(idx);
      if (!in_inventory(slot) && !is_equipped(slot))
        return false;
    }

    return true;
  }

  bool equip(Equipment::SLOT slot) const {
    return true;
  }

  auto begin() { return _set.begin(); }
  auto begin() const { return _set.begin(); }

  auto end() { return _set.end(); }
  auto end() const { return _set.end(); }

  auto cbegin() { return _set.cbegin(); }
  auto cbegin() const { return _set.cbegin(); }

  auto cend() { return _set.cend(); }
  auto cend() const { return _set.cend(); }

private:
  auto &_get(Equipment::SLOT slot) {
    return _set[static_cast<std::size_t>(slot)];
  }

  const auto &_get(Equipment::SLOT slot) const {
    return _set[static_cast<std::size_t>(slot)];
  }

  std::array<std::optional<ItemIdentifier>, 11> _set;
};
} // namespace ab
#pragma once

#include <regex>
#include <string>
#include <vector>
#include <string_view>

#include <Game/Core.hpp>

namespace ab {
class equippable {
public:
  std::regex name_pattern;
  Equipment::SLOT slot;

  equippable();
  equippable(const equippable &other);
  equippable(equippable &&other);
  equippable &operator=(const equippable &other);
  equippable &operator=(equippable &&other) noexcept;

  equippable(std::string_view name_pattern,
             Equipment::SLOT slot);
  
  bool has() const;

  bool equipped() const;

  bool equip() const;
};
} // namespace ab
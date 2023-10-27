#pragma once

#include <string>

#include <Game/Core.hpp>

namespace ab {
class prayer_manager {
public:
  std::unordered_map<std::string,
                     std::vector<Prayer::PRAYERS>>
      switches;

  prayer_manager();

  ~prayer_manager();

  bool is_active(const std::string &switch_name) const;
  
  bool activate(const std::string &switch_name) const;
};
} // namespace ab
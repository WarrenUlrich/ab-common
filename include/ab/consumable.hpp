#pragma once

#include <string_view>
#include <regex>

namespace ab {
  class consumable {
  public:
    std::regex name_pattern;
  };
}
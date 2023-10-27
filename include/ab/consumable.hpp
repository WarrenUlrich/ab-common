#pragma once

#include <string_view>
#include <regex>

namespace ab {
  class consumable {
  public:
    std::regex name_pattern;

    consumable();
    ~consumable();

    consumable(const consumable& other);
    consumable(consumable &&other);

    consumable(std::string_view name_pattern);

    bool has() const;
    
    virtual bool consume() const = 0;
  };
}
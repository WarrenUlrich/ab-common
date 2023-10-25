#pragma once

#include <string>

namespace ab {
  class consumable {
  public:
    std::string name;

    virtual bool has() const;

    virtual bool use() const = 0;
  };
}
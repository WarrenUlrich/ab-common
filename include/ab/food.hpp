#pragma once

#include <regex>

#include "consumable.hpp"

namespace ab {
  class food : public consumable {
  public:
    std::int32_t regeneration;

    food();
    ~food();

    food(const food& other);
    food(food &&other);

    food(std::int32_t regeneration);

    bool consume() const override;
  };
}
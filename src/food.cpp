#include <ab/food.hpp>

#include <Game/Core.hpp>

namespace ab {
food::food() = default;

food::~food() = default;

food::food(const food &other)
    : regeneration(other.regeneration) {}

food::food(food &&other)
    : regeneration(other.regeneration) {}

food::food(std::int32_t regeneration)
    : regeneration(regeneration) {}

bool food::consume() const {
  const auto item = Inventory::GetItem(name_pattern);
  if (!item)
    return false;

  return item.Interact("Eat");
}
} // namespace ab
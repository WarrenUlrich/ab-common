#include <ab/consumable.hpp>

#include <Game/Core.hpp>

namespace ab {
bool consumable::has() const {
  return Inventory::Contains(this->name);
}

bool consumable::use() const {
  return true;
}
} // namespace ab
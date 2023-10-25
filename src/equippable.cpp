#include <ab/equippable.hpp>

#include <Game/Core.hpp>

namespace ab {
equippable::equippable() = default;

equippable::equippable(const equippable &other)
    : name_pattern(other.name_pattern), slot(other.slot) {}

equippable::equippable(equippable &&other)
    : name_pattern(std::move(other.name_pattern)),
      slot(std::move(other.slot)) {}

equippable::equippable(const std::string &pattern,
                       Equipment::SLOT slot)
    : name_pattern(pattern), slot(slot) {}

equippable &equippable::operator=(const equippable &other) {
  this->name_pattern = other.name_pattern;
  this->slot = other.slot;
  return *this;
}

equippable &
equippable::operator=(equippable &&other) noexcept {
  this->name_pattern = std::move(other.name_pattern);
  this->slot = std::move(other.slot);
  return *this;
}

bool equippable::has() const {
  if (equipped())
    return true;

  const auto item = Inventory::GetItem(name_pattern);
  if (!item)
    return false;

  return true;
}

bool equippable::equipped() const {
  const auto equipped = Equipment::GetItem(this->slot);
  if (!equipped)
    return false;

  if (!std::regex_match(equipped.GetName(),
                        this->name_pattern))
    return false;

  return true;
}

bool equippable::equip() const {
  if (this->equipped())
    return true;

  const auto item = Inventory::GetItem(this->name_pattern);
  if (!item)
    return false;

  static auto options = std::array<std::string, 4>{
      "Wield", "Wear", "Equip", "Put on"};

  for (const auto &option : options) {
    if (item.Interact(option)) {
      if (WaitFunc(1000, 50,
                   [&]() { return this->equipped(); })) {
        return true;
      }
    }
  }

  return false;
}
} // namespace ab
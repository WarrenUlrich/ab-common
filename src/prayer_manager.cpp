#include <ab/prayer_manager.hpp>

namespace ab {
prayer_manager::prayer_manager() = default;

prayer_manager::~prayer_manager() = default;

bool prayer_manager::is_active(
    const std::string &switch_name) const {
  auto &prayers = switches.at(switch_name);
  for (const auto &prayer : prayers) {
    if (!Prayer::IsActive(prayer))
      return false;
  }

  return true;
}

bool prayer_manager::activate(
    const std::string &switch_name) const {
  auto &prayers = switches.at(switch_name);
  for (const auto &prayer : prayers) {
    if (!Prayer::Activate(prayer))
      return false;
  }

  return true;
}
} // namespace ab
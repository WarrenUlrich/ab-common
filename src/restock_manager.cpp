#include <ab/restock_manager.hpp>

namespace ab {
restock_request::restock_request()
    : item_name(""), amount(0) {}

restock_request::~restock_request() {}

restock_request::restock_request(
    const std::string &item_name, std::int32_t amount)
    : item_name(item_name), amount(amount) {}

restock_request::restock_request(
    const restock_request &other)
    : item_name(other.item_name), amount(other.amount) {}

restock_request::restock_request(restock_request &&other)
    : item_name(std::move(other.item_name)),
      amount(other.amount) {
  other.amount = 0;
}

restock_request &
restock_request::operator=(const restock_request &other) {
  if (this != &other) {
    item_name = other.item_name;
    amount = other.amount;
  }
  return *this;
}

restock_request &
restock_request::operator=(restock_request &&other) {
  if (this != &other) {
    item_name = std::move(other.item_name);
    amount = other.amount;
    other.amount = 0;
  }
  return *this;
}

restock_order::restock_order() {}

restock_order::~restock_order() {}

restock_order::restock_order(const restock_order &other)
    : slot(other.slot) {}

restock_order::restock_order(restock_order &&other)
    : slot(std::move(other.slot)) {}

restock_order &
restock_order::operator=(const restock_order &other) {
  if (this != &other) {
    slot = other.slot;
  }
  return *this;
}

restock_order &
restock_order::operator=(restock_order &&other) {
  if (this != &other) {
    slot = std::move(other.slot);
  }
  return *this;
}

restock_manager &
restock_manager::operator=(const restock_manager &other) {
  if (this != &other) {
    this->sell_requests = other.sell_requests;
    this->buy_requests = other.buy_requests;
    this->active_orders = other.active_orders;
  }
  return *this;
}

restock_manager &
restock_manager::operator=(restock_manager &&other) {
  if (this != &other) {
    this->sell_requests = std::move(other.sell_requests);
    this->buy_requests = std::move(other.buy_requests);
    this->active_orders = std::move(other.active_orders);
  }
  return *this;
}
} // namespace ab

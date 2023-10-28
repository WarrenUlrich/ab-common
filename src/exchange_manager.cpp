#include <ab/exchange_manager.hpp>

#include <utility>

namespace ab {
exchange_request::exchange_request()
    : item_name(""), quantity(0) {}

exchange_request::~exchange_request() {}

exchange_request::exchange_request(
    const std::string &item_name, std::int32_t amount,
    std::int32_t price, Exchange::SLOT_MODE mode)
    : item_name(item_name), quantity(quantity),
      price(price), mode(mode) {}

exchange_request::exchange_request(
    const exchange_request &other)
    : item_name(other.item_name), quantity(other.quantity),
      price(other.price), mode(other.mode) {}

exchange_request::exchange_request(exchange_request &&other)
    : item_name(std::move(other.item_name)),
      quantity(std::exchange(other.quantity, 0)),
      price(std::exchange(other.price, 0)),
      mode(std::exchange(other.mode,
                         Exchange::MODE_UNDEFINED)) {}

exchange_request &
exchange_request::operator=(const exchange_request &other) {
  if (this != &other) {
    item_name = other.item_name;
    quantity = other.quantity;
    price = other.price;
    mode = other.mode;
  }
  return *this;
}

exchange_request &
exchange_request::operator=(exchange_request &&other) {
  if (this != &other) {
    item_name = std::move(other.item_name);
    quantity = std::exchange(other.price, 0);
    price = std::exchange(other.price, 0);
    mode =
        std::exchange(other.mode, Exchange::MODE_UNDEFINED);
  }
  return *this;
}

exchange_order::exchange_order() {}

exchange_order::~exchange_order() {}

exchange_order::exchange_order(const exchange_order &other)
    : slot(other.slot) {}

exchange_order::exchange_order(exchange_order &&other)
    : slot(std::exchange(other.slot,
                         Exchange::STATE_EMPTY)) {}

exchange_order &
exchange_order::operator=(const exchange_order &other) {
  if (this != &other) {
    slot = other.slot;
  }
  return *this;
}

exchange_order &
exchange_order::operator=(exchange_order &&other) {
  if (this != &other) {
    slot = std::exchange(other.slot, Exchange::STATE_EMPTY);
  }
  return *this;
}

exchange_order::exchange_order(
    Exchange::SLOT slot, const exchange_request &request)
    : slot(slot), request(request) {}

Exchange::SLOT_STATE exchange_order::get_state() const {
  return Exchange::GetSlotState(slot);
}

bool exchange_order::collect(
    Exchange::COLLECT_METHOD method) const {
  const auto state = get_state();
  switch (request.mode) {
  case Exchange::BUY:
    if (state != Exchange::BUY_OFFER_COMPLETE)
      return false;
    break;
  case Exchange::SELL:
    if (state != Exchange::SELL_OFFER_COMPLETE)
      return false;
    break;
  default:
    return false;
  }

  if (!Exchange::OpenOffer(slot))
    return false;

  return Exchange::Collect(method);
}

exchange_manager &
exchange_manager::operator=(const exchange_manager &other) {
  if (this != &other) {
    this->active_orders = other.active_orders;
  }
  return *this;
}

exchange_manager &
exchange_manager::operator=(exchange_manager &&other) {
  if (this != &other) {
    this->active_orders = std::move(other.active_orders);
  }
  return *this;
}

bool exchange_manager::place_order(
    const exchange_request &request) {
  if (!Exchange::IsOpen())
    return false;

  const auto slot = _get_usable_slot();
  if (!slot.has_value())
    return false;

  switch (request.mode) {
  case Exchange::BUY:
    if (!Exchange::OpenBuyOffer())
      return false;
    break;
  case Exchange::SELL:
    if (!Exchange::OpenSellOffer())
      return false;
    break;
  default:
    return false;
  }

  if (!Exchange::SetBuyItem(request.item_name))
    return false;

  if (!Exchange::SetOfferPrice(request.price))
    return false;

  if (!Exchange::SetOfferAmount(request.quantity))
    return false;

  if (!Exchange::ConfirmOffer())
    return false;

  active_orders.emplace_back(slot.value(), request);
  return true;
}

std::optional<Exchange::SLOT> _get_usable_slot() {
  for (Exchange::SLOT idx = 0; idx < 8; ++idx) {
    if (Exchange::SlotUsable(idx))
      return idx;
  }

  return std::nullopt;
}
} // namespace ab

#pragma once

#include <optional>
#include <vector>

#include <Game/Core.hpp>

namespace ab {
class exchange_request {
public:
  std::string item_name;
  std::int32_t quantity;
  std::int32_t price;
  Exchange::SLOT_MODE mode;

  exchange_request();
  ~exchange_request();

  exchange_request(const std::string &item_name,
                  std::int32_t quantity,
                  std::int32_t price, Exchange::SLOT_MODE mode);

  exchange_request(const exchange_request &other);
  exchange_request(exchange_request &&other);

  exchange_request &operator=(const exchange_request &other);
  exchange_request &operator=(exchange_request &&other);
};

class exchange_order {
public:
  Exchange::SLOT slot;
  exchange_request request;

  exchange_order();
  ~exchange_order();

  exchange_order(const exchange_order &other);
  exchange_order(exchange_order &&other);

  exchange_order &operator=(const exchange_order &other);
  exchange_order &operator=(exchange_order &&other);

  exchange_order(Exchange::SLOT slot, const exchange_request &request);

  Exchange::SLOT_STATE get_state() const;

  bool collect(Exchange::COLLECT_METHOD method = Exchange::BANK) const;
};

class exchange_manager {
public:
  std::vector<exchange_order> active_orders;

  exchange_manager(const exchange_manager &other);
  exchange_manager(exchange_manager &&other);

  exchange_manager &operator=(const exchange_manager &other);
  exchange_manager &operator=(exchange_manager &&other);

  bool place_order(const exchange_request &request);

private:
  static std::optional<Exchange::SLOT> _get_usable_slot();
};
} // namespace ab
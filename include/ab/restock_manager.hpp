#pragma once

#include <Game/Core.hpp>

#include <queue>

namespace ab {
  class restock_request {
  public:
    std::string item_name;
    std::int32_t amount;

    restock_request();
    ~restock_request();

    restock_request(const std::string &item_name, std::int32_t amount);

    restock_request(const restock_request &other);
    restock_request(restock_request&& other);

    restock_request& operator=(const restock_request &other);
    restock_request& operator=(restock_request &&other);
  };

  class restock_order {
  public:
    Exchange::SLOT slot;

    restock_order();
    ~restock_order();

    restock_order(const restock_order&other);
    restock_order(restock_order &&other);

    restock_order& operator=(const restock_order &other);
    restock_order& operator=(restock_order &&other);
  };
  
  class restock_manager {
  public:
    std::queue<restock_request> buy_requests;
    std::queue<restock_request> sell_requests;

    std::queue<restock_order> active_orders;

    restock_manager(const restock_manager&other);
    restock_manager(restock_manager &&other);

    restock_manager& operator=(const restock_manager &other);
    restock_manager& operator=(restock_manager &&other);
  };
}
#pragma once
#include <vector>
#include <string>
#include "OrderItem.h"

enum class OrderStatus {
    CREATED,
    PAID,
    IN_PROCESS,
    SHIPPED,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    int id;
    int customerId;
    std::string createdAt;
    OrderStatus status;
    std::vector<OrderItem> items;
    double totalAmount;
public:
    Order(int id, int customerId, const std::string& createdAt)
        : id(id), customerId(customerId), createdAt(createdAt),
          status(OrderStatus::CREATED), totalAmount(0.0) {}

    void addItem(const Product& product, int quantity) {
        items.emplace_back(product, quantity);
        totalAmount += product.getPrice() * quantity;
    }

    void place() { status = OrderStatus::IN_PROCESS; }
    void cancel() { status = OrderStatus::CANCELLED; }
    void markPaid() { status = OrderStatus::PAID; }

    double getTotalAmount() const { return totalAmount; }
    int getCustomerId() const { return customerId; }
};

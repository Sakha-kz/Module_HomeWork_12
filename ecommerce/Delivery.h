#pragma once
#include <string>

enum class DeliveryStatus { CREATED, IN_TRANSIT, DELIVERED, CANCELLED };

class Delivery {
private:
    int id;
    int orderId;
    std::string address;
    std::string courierName;
    DeliveryStatus status;
public:
    Delivery(int id, int orderId,
             const std::string& address,
             const std::string& courierName)
        : id(id), orderId(orderId), address(address),
          courierName(courierName), status(DeliveryStatus::CREATED) {}

    void send() { status = DeliveryStatus::IN_TRANSIT; }
    void track() const { /* можно выводить статус */ }
    void complete() { status = DeliveryStatus::DELIVERED; }
};

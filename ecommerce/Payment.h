#pragma once
#include <string>

enum class PaymentType { CARD, WALLET };
enum class PaymentStatus { PENDING, SUCCESS, FAILED, REFUNDED };

class Payment {
private:
    int id;
    PaymentType type;
    double amount;
    PaymentStatus status;
    std::string date;
public:
    Payment(int id, PaymentType type, double amount, const std::string& date)
        : id(id), type(type), amount(amount), status(PaymentStatus::PENDING), date(date) {}

    void process() {
        status = PaymentStatus::SUCCESS;
    }

    void refund() {
        if (status == PaymentStatus::SUCCESS)
            status = PaymentStatus::REFUNDED;
    }
};

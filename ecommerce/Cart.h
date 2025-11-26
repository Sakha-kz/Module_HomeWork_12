#pragma once
#include <vector>
#include <memory>
#include "CartItem.h"
#include "DiscountStrategy.h"

class Cart {
private:
    int customerId;
    std::vector<CartItem> items;
    std::shared_ptr<DiscountStrategy> discount;  
public:
    Cart(int customerId) : customerId(customerId) {}

    void addItem(const Product& product, int quantity) {
        items.emplace_back(product, quantity);
    }

    void setDiscount(const std::shared_ptr<DiscountStrategy>& disc) {
        discount = disc;
    }

    double calculateTotal() const {
        double sum = 0.0;
        for (const auto& item : items)
            sum += item.getLineTotal();

        if (discount)
            sum = discount->apply(sum);

        return sum;
    }
};

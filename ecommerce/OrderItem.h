#pragma once
#include "Product.h"

class OrderItem {
private:
    Product product;
    int quantity;
public:
    OrderItem(const Product& p, int q) : product(p), quantity(q) {}
    double getLineTotal() const { return product.getPrice() * quantity; }
};

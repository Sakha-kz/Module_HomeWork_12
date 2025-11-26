#pragma once
#include "Product.h"

class CartItem {
private:
    Product product;
    int quantity;
public:
    CartItem(const Product& p, int q) : product(p), quantity(q) {}
    double getLineTotal() const { return product.getPrice() * quantity; }
    const Product& getProduct() const { return product; }
    int getQuantity() const { return quantity; }
};

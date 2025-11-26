#include <iostream>
#include <memory>
#include <algorithm>
#include "Customer.h"
#include "Product.h"
#include "Cart.h"
#include "PromoCodeDiscount.h"
#include "Order.h"
#include "Payment.h"
#include "Delivery.h"

int main() {
    Customer c(1, "Alice", "alice@mail.com", "Main street 1", "+123");
    Product p1(1, "Phone", "Smartphone", 300.0, 10, 1);
    Product p2(2, "Case", "Phone case", 20.0, 50, 1);

    Cart cart(c.getId());
    cart.addItem(p1, 1);
    cart.addItem(p2, 2);

    auto discount = std::make_shared<PromoCodeDiscount>("NEW10", 0.10);
    cart.setDiscount(discount);

    double total = cart.calculateTotal();
    std::cout << "Cart total with discount: " << total << "\n";

    Order order(1, c.getId(), "2025-11-26");
    order.addItem(p1, 1);
    order.addItem(p2, 2);
    order.place();

    Payment payment(1, PaymentType::CARD, order.getTotalAmount(), "2025-11-26");
    payment.process();

    Delivery delivery(1, 1, "Main street 1", "Courier John");
    delivery.send();

    return 0;
}
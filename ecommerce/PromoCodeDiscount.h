#pragma once
#include "DiscountStrategy.h"

class PromoCodeDiscount : public DiscountStrategy {
    std::string code;
    double percent; 
public:
    PromoCodeDiscount(const std::string& code, double percent)
        : code(code), percent(percent) {}

    double apply(double originalAmount) const override {
        return originalAmount * (1.0 - percent);
    }

    std::string getDescription() const override {
        return "Promo code " + code + " (" + std::to_string(int(percent * 100)) + "%)";
    }
};

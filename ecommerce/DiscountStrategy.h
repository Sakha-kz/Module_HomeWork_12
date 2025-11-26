#pragma once
#include <string>

class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    virtual double apply(double originalAmount) const = 0;
    virtual std::string getDescription() const = 0;
};

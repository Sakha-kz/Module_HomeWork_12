#pragma once

class LoyaltyAccount {
private:
    int customerId;
    int points;
public:
    LoyaltyAccount(int customerId) : customerId(customerId), points(0) {}

    void addPoints(int amount) { points += amount; }
    bool redeemPoints(int amount) {
        if (points >= amount) {
            points -= amount;
            return true;
        }
        return false;
    }

    int getPoints() const { return points; }
};

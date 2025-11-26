#pragma once
#include "User.h"
#include <iostream>

class Admin : public User {
public:
    Admin(int id,
          const std::string& name,
          const std::string& email,
          const std::string& address,
          const std::string& phone)
        : User(id, name, email, address, phone, "admin") {}

    void registerUser() override;
    bool login(const std::string& email, const std::string& password) override;

    void logAction(const std::string& action) {
        std::cout << "[ADMIN LOG] " << name << ": " << action << "\n";
    }
};

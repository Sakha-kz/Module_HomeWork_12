#pragma once
#include "User.h"
#include <iostream>

class Customer : public User {
public:
    Customer(int id,
             const std::string& name,
             const std::string& email,
             const std::string& address,
             const std::string& phone)
        : User(id, name, email, address, phone, "customer") {}

    void registerUser() override {
        std::cout << "Регистрация покупателя: " << getName() << std::endl;
    }
    
    bool login(const std::string& email, const std::string& password) override {
        std::cout << "Вход покупателя: " << email << std::endl;
        (void)password; 
        return true;
    }
};
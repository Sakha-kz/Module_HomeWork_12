#pragma once
#include <string>

class User {
protected:
    int id;
    std::string name;
    std::string email;
    std::string address;
    std::string phone;
    std::string role;

public:
    User(int id, const std::string& name, const std::string& email,
         const std::string& address, const std::string& phone, const std::string& role)
        : id(id), name(name), email(email), address(address), phone(phone), role(role) {}

    virtual ~User() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    
    virtual void registerUser() = 0;
    virtual bool login(const std::string& email, const std::string& password) = 0;
};
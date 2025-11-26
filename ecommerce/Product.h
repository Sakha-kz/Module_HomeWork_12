#pragma once
#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string description;
    double price;
    int stockQuantity;
    int categoryId;
public:
    Product(int id,
            const std::string& name,
            const std::string& description,
            double price,
            int stockQuantity,
            int categoryId)
        : id(id), name(name), description(description),
          price(price), stockQuantity(stockQuantity), categoryId(categoryId) {}

    void create() { /* ... */ }
    void update(const std::string& newName,
                const std::string& newDescription,
                double newPrice,
                int newStock) {
        name = newName;
        description = newDescription;
        price = newPrice;
        stockQuantity = newStock;
    }
    void remove() { /* ... */ }

    int getId() const { return id; }
    double getPrice() const { return price; }
};

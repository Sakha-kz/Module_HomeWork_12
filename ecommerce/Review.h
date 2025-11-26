#pragma once
#include <string>

class Review {
private:
    int id;
    int productId;
    int customerId;
    int rating;
    std::string comment;
public:
    Review(int id, int productId, int customerId,
           int rating, const std::string& comment)
        : id(id), productId(productId), customerId(customerId),
          rating(rating), comment(comment) {}
};

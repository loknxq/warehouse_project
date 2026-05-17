// warehouse_project/include/core/Stock.h
#ifndef STOCK_H
#define STOCK_H

#include "Product.h"
#include <memory>
#include <vector>
#include <functional>

class Stock {
private:
    std::shared_ptr<Product> product;
    int currentQuantity;
    std::vector<std::function<void(int, int)>> observers;

public:
    Stock();
    explicit Stock(std::shared_ptr<Product> product, int quantity = 0);
    
    std::shared_ptr<Product> getProduct() const;
    int getCurrentQuantity() const;
    
    void addQuantity(int amount);
    bool removeQuantity(int amount);
    void setQuantity(int newQuantity);
    
    bool isBelowMinStock() const;
    int getRecommendedOrderQuantity(int avgDailySales, int deliveryDays) const;
    
    void addObserver(std::function<void(int, int)> observer);
    void notifyObservers();
    
    bool operator==(const Stock& other) const;
};

#endif
#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include "core/Product.h"

class Observer {
public:
    virtual void update(int productId, int newQuantity) = 0;
    virtual ~Observer() {}
};

class Stock {
private:
    int productId;
    int currentQuantity;
    int minThreshold;
    std::vector<Observer*> observers;

public:
    Stock();
    Stock(int productId, int currentQuantity, int minThreshold);

    int getProductId() const;
    int getCurrentQuantity() const;
    int getMinThreshold() const;

    void setQuantity(int newQuantity);
    void increaseQuantity(int amount);
    void decreaseQuantity(int amount);
    bool hasEnough(int requestedAmount) const;

    void attach(Observer* obs);
    void detach(Observer* obs);
    void notifyObservers();
};

#endif
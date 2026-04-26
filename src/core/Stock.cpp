#include "core/Stock.h"

Stock::Stock() {
    productId = 0;
    currentQuantity = 0;
    minThreshold = 0;
}

Stock::Stock(int productId, int currentQuantity, int minThreshold) {
    this->productId = productId;
    this->currentQuantity = currentQuantity;
    this->minThreshold = minThreshold;
}

int Stock::getProductId() const { return productId; }
int Stock::getCurrentQuantity() const { return currentQuantity; }
int Stock::getMinThreshold() const { return minThreshold; }

void Stock::setQuantity(int newQuantity) {
    currentQuantity = newQuantity;
    notifyObservers();
}

void Stock::increaseQuantity(int amount) {
    currentQuantity += amount;
    notifyObservers();
}

void Stock::decreaseQuantity(int amount) {
    if (currentQuantity >= amount) {
        currentQuantity -= amount;
        notifyObservers();
    }
}

bool Stock::hasEnough(int requestedAmount) const {
    return currentQuantity >= requestedAmount;
}

void Stock::attach(Observer* obs) {
    observers.push_back(obs);
}

void Stock::detach(Observer* obs) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == obs) {
            observers.erase(it);
            break;
        }
    }
}

void Stock::notifyObservers() {
    for (auto obs : observers) {
        obs->update(productId, currentQuantity);
    }
}
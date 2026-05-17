// warehouse_project/src/core/Stock.cpp
#include "../../include/core/Stock.h"

Stock::Stock() : product(nullptr), currentQuantity(0) {}

Stock::Stock(std::shared_ptr<Product> product, int quantity)
    : product(product), currentQuantity(quantity) {}

std::shared_ptr<Product> Stock::getProduct() const { return product; }
int Stock::getCurrentQuantity() const { return currentQuantity; }

void Stock::addQuantity(int amount) {
    if (amount > 0) {
        currentQuantity += amount;
        notifyObservers();
    }
}

bool Stock::removeQuantity(int amount) {
    if (amount > 0 && amount <= currentQuantity) {
        currentQuantity -= amount;
        notifyObservers();
        return true;
    }
    return false;
}

void Stock::setQuantity(int newQuantity) {
    if (newQuantity >= 0) {
        currentQuantity = newQuantity;
        notifyObservers();
    }
}

bool Stock::isBelowMinStock() const {
    if (!product) return false;
    return currentQuantity < product->getMinStock();
}

int Stock::getRecommendedOrderQuantity(int avgDailySales, int deliveryDays) const {
    if (!product) return 0;
    int safetyStock = avgDailySales * deliveryDays;
    int deficit = product->getMinStock() - currentQuantity;
    return (deficit > 0 ? deficit : 0) + safetyStock;
}

void Stock::addObserver(std::function<void(int, int)> observer) {
    observers.push_back(observer);
}

void Stock::notifyObservers() {
    if (!product) return;
    for (auto& observer : observers) {
        observer(product->getId(), currentQuantity);
    }
}

bool Stock::operator==(const Stock& other) const {
    if (!product || !other.product) return false;
    return product->getId() == other.product->getId() && 
           currentQuantity == other.currentQuantity;
}
#include "services/OrderCalculator.h"

OrderCalculator::OrderCalculator() {
    strategy = nullptr;
}

void OrderCalculator::setStrategy(RecommendationStrategy* strategy) {
    this->strategy = strategy;
}

int OrderCalculator::calculateRecommendation(int productId, int currentStock, int minStock) {
    if (strategy == nullptr) {
        // Если стратегия не установлена, возвращаем простую разницу
        return (minStock - currentStock) > 0 ? (minStock - currentStock) : 0;
    }
    return strategy->calculate(productId, currentStock, minStock);
}
// warehouse_project/src/services/OrderCalculator.cpp
#include "../../include/services/OrderCalculator.h"

OrderCalculator::OrderCalculator(std::shared_ptr<RecommendationStrategy> strategy)
    : strategy(strategy) {}

void OrderCalculator::setStrategy(std::shared_ptr<RecommendationStrategy> newStrategy) {
    strategy = newStrategy;
}

int OrderCalculator::calculateRecommendedQuantity(int currentStock, int minStock,
                                                    int avgDailySales, int deliveryDays) {
    if (!strategy) return 0;
    return strategy->calculate(currentStock, minStock, avgDailySales, deliveryDays);
}

std::string OrderCalculator::getCurrentStrategyName() const {
    if (!strategy) return "No strategy";
    return strategy->getName();
}
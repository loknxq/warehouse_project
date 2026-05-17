// warehouse_project/include/services/OrderCalculator.h
#ifndef ORDER_CALCULATOR_H
#define ORDER_CALCULATOR_H

#include "../strategies/RecommendationStrategy.h"
#include <memory>

class OrderCalculator {
private:
    std::shared_ptr<RecommendationStrategy> strategy;

public:
    explicit OrderCalculator(std::shared_ptr<RecommendationStrategy> strategy);
    
    void setStrategy(std::shared_ptr<RecommendationStrategy> newStrategy);
    int calculateRecommendedQuantity(int currentStock, int minStock, 
                                      int avgDailySales, int deliveryDays);
    std::string getCurrentStrategyName() const;
};

#endif
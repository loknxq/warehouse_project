#ifndef ORDER_CALCULATOR_H
#define ORDER_CALCULATOR_H

#include "strategies/RecommendationStrategy.h"

class OrderCalculator {
private:
    RecommendationStrategy* strategy;

public:
    OrderCalculator();
    void setStrategy(RecommendationStrategy* strategy);
    int calculateRecommendation(int productId, int currentStock, int minStock);
};

#endif
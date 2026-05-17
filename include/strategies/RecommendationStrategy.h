// warehouse_project/include/strategies/RecommendationStrategy.h
#ifndef RECOMMENDATION_STRATEGY_H
#define RECOMMENDATION_STRATEGY_H

#include <string>

class RecommendationStrategy {
public:
    virtual ~RecommendationStrategy() = default;
    virtual int calculate(int currentStock, int minStock, 
                          int avgDailySales, int deliveryDays) = 0;
    virtual std::string getName() const = 0;
};

#endif
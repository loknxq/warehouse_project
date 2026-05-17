// warehouse_project/include/strategies/AverageSalesStrategy.h
#ifndef AVERAGE_SALES_STRATEGY_H
#define AVERAGE_SALES_STRATEGY_H

#include "RecommendationStrategy.h"

class AverageSalesStrategy : public RecommendationStrategy {
public:
    int calculate(int currentStock, int minStock, 
                  int avgDailySales, int deliveryDays) override;
    std::string getName() const override;
};

#endif
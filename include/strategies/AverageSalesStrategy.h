#ifndef AVERAGE_SALES_STRATEGY_H
#define AVERAGE_SALES_STRATEGY_H

#include "strategies/RecommendationStrategy.h"

class AverageSalesStrategy : public RecommendationStrategy {
private:
    int getAverageDailySales(int productId);
    int getLeadTime(int productId);

public:
    int calculate(int productId, int currentStock, int minStock) override;
};

#endif
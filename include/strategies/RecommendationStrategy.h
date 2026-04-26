#ifndef RECOMMENDATION_STRATEGY_H
#define RECOMMENDATION_STRATEGY_H

class RecommendationStrategy {
public:
    virtual ~RecommendationStrategy() {}
    virtual int calculate(int productId, int currentStock, int minStock) = 0;
};

#endif
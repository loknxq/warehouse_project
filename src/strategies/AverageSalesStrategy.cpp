// warehouse_project/src/strategies/AverageSalesStrategy.cpp
#include "../../include/strategies/AverageSalesStrategy.h"

int AverageSalesStrategy::calculate(int currentStock, int minStock,
                                     int avgDailySales, int deliveryDays) {
    // Обработка отрицательных значений
    if (currentStock < 0) currentStock = 0;
    if (minStock < 0) minStock = 0;
    if (avgDailySales < 0) avgDailySales = 0;
    if (deliveryDays < 0) deliveryDays = 0;
    
    int deficit = minStock - currentStock;
    if (deficit < 0) deficit = 0;
    return deficit + (avgDailySales * deliveryDays);
}

std::string AverageSalesStrategy::getName() const {
    return "Average Sales Strategy (30 days)";
}
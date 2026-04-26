#include "strategies/AverageSalesStrategy.h"
#include <iostream>

int AverageSalesStrategy::getAverageDailySales(int productId) {
    // В реальном проекте здесь был бы запрос к базе данных
    // Для примера возвращаем фиктивные значения
    if (productId == 1) return 5;
    if (productId == 2) return 2;
    return 3;
}

int AverageSalesStrategy::getLeadTime(int productId) {
    // В реальном проекте время доставки зависит от поставщика
    // Для примера возвращаем фиктивные значения
    if (productId == 1) return 3;
    if (productId == 2) return 7;
    return 5;
}

int AverageSalesStrategy::calculate(int productId, int currentStock, int minStock) {
    int avgDailySales = getAverageDailySales(productId);
    int leadTimeDays = getLeadTime(productId);
    
    int safetyStock = avgDailySales * leadTimeDays;
    int needed = (minStock - currentStock) + safetyStock;
    
    if (needed < 0) {
        needed = 0;
    }
    
    std::cout << "Стратегия средних продаж: товар " << productId 
              << ", текущий остаток " << currentStock 
              << ", минимальный порог " << minStock
              << ", рекомендуемый заказ " << needed << std::endl;
    
    return needed;
}
// warehouse_project/tests/test_order_calculator.cpp
#include <catch2/catch_test_macros.hpp>
#include "../include/services/OrderCalculator.h"
#include "../include/strategies/AverageSalesStrategy.h"
#include <memory>

TEST_CASE("OrderCalculator tests", "[OrderCalculator]") {
    
    auto strategy = std::make_shared<AverageSalesStrategy>();
    OrderCalculator calculator(strategy);
    
    SECTION("Constructor sets strategy correctly") {
        REQUIRE(calculator.getCurrentStrategyName() == "Average Sales Strategy (30 days)");
    }
    
    SECTION("calculateRecommendedQuantity works with strategy") {
        // currentStock=10, minStock=20, avgDailySales=2, deliveryDays=5
        // deficit=10, result = 10 + (2*5)=20
        int result = calculator.calculateRecommendedQuantity(10, 20, 2, 5);
        REQUIRE(result == 20);
        
        // currentStock=25, minStock=20 (no deficit), result = 0 + (3*7)=21
        result = calculator.calculateRecommendedQuantity(25, 20, 3, 7);
        REQUIRE(result == 21);
        
        // currentStock=0, minStock=10, result = 10 + (5*2)=20
        result = calculator.calculateRecommendedQuantity(0, 10, 5, 2);
        REQUIRE(result == 20);
    }
    
    SECTION("setStrategy changes strategy") {
        auto newStrategy = std::make_shared<AverageSalesStrategy>();
        calculator.setStrategy(newStrategy);
        
        REQUIRE(calculator.getCurrentStrategyName() == "Average Sales Strategy (30 days)");
        
        int result = calculator.calculateRecommendedQuantity(10, 20, 2, 5);
        REQUIRE(result == 20);
    }
    
    SECTION("calculateRecommendedQuantity handles edge cases") {
        // Zero delivery days
        int result = calculator.calculateRecommendedQuantity(10, 15, 3, 0);
        REQUIRE(result == 5); // deficit only
        
        // Zero avg daily sales
        result = calculator.calculateRecommendedQuantity(10, 15, 0, 5);
        REQUIRE(result == 5);
        
        // Both zero
        result = calculator.calculateRecommendedQuantity(10, 15, 0, 0);
        REQUIRE(result == 5);
        
        // Current stock above min stock, zero sales, zero delivery
        result = calculator.calculateRecommendedQuantity(20, 15, 0, 0);
        REQUIRE(result == 0);
    }
    
    SECTION("Calculator handles null strategy gracefully") {
        OrderCalculator calc(nullptr);
        int result = calc.calculateRecommendedQuantity(10, 20, 2, 5);
        REQUIRE(result == 0);
        REQUIRE(calc.getCurrentStrategyName() == "No strategy");
    }
}
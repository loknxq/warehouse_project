#include <catch2/catch_test_macros.hpp>
#include "../include/strategies/AverageSalesStrategy.h"

TEST_CASE("AverageSalesStrategy tests", "[Strategy]") {
    
    AverageSalesStrategy strategy;
    
    SECTION("calculate returns correct values") {
        REQUIRE(strategy.calculate(10, 20, 2, 5) == 20);
        
        REQUIRE(strategy.calculate(25, 20, 3, 7) == 21);
        
        REQUIRE(strategy.calculate(5, 10, 10, 3) == 35); // 5 deficit + 30
        
        REQUIRE(strategy.calculate(10, 15, 2, 10) == 25); // 5 deficit + 20
    }
    
    SECTION("calculate handles edge cases") {
        REQUIRE(strategy.calculate(0, 10, 3, 4) == 22); // 10 deficit + 12
        
        REQUIRE(strategy.calculate(5, 0, 2, 3) == 6); // 0 deficit + 6
        
        REQUIRE(strategy.calculate(100, 1000, 50, 30) == 2400); // 900 deficit + 1500
        
        REQUIRE(strategy.calculate(-5, 10, 2, 3) == 16);
        
        REQUIRE(strategy.calculate(-10, -5, -2, -3) == 0); 
    }
    
    SECTION("getName returns correct string") {
        REQUIRE(strategy.getName() == "Average Sales Strategy (30 days)");
    }
    
    SECTION("Multiple strategy instances work independently") {
        AverageSalesStrategy s1, s2;
        
        REQUIRE(s1.calculate(10, 20, 2, 5) == s2.calculate(10, 20, 2, 5));
        REQUIRE(s1.getName() == s2.getName());
    }
}
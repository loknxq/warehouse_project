#include <catch2/catch_test_macros.hpp>
#include "../include/core/Stock.h"
#include "../include/core/Product.h"
#include <memory>

TEST_CASE("Stock class tests", "[Stock]") {
    
    auto product = std::make_shared<Product>(1, "Test Product", "T001", "Category", "pcs", 100.0, 150.0, 10);
    
    SECTION("Default constructor") {
        Stock s;
        REQUIRE(s.getProduct() == nullptr);
        REQUIRE(s.getCurrentQuantity() == 0);
    }
    
    SECTION("Parameterized constructor") {
        Stock s(product, 50);
        REQUIRE(s.getProduct() == product);
        REQUIRE(s.getCurrentQuantity() == 50);
    }
    
    SECTION("addQuantity increases quantity") {
        Stock s(product, 10);
        s.addQuantity(5);
        REQUIRE(s.getCurrentQuantity() == 15);
        
        s.addQuantity(0);
        REQUIRE(s.getCurrentQuantity() == 15);
        
        s.addQuantity(100);
        REQUIRE(s.getCurrentQuantity() == 115);
    }
    
    SECTION("removeQuantity decreases quantity when sufficient stock") {
        Stock s(product, 20);
        REQUIRE(s.removeQuantity(5) == true);
        REQUIRE(s.getCurrentQuantity() == 15);
        
        REQUIRE(s.removeQuantity(15) == true);
        REQUIRE(s.getCurrentQuantity() == 0);
    }
    
    SECTION("removeQuantity fails when insufficient stock") {
        Stock s(product, 10);
        REQUIRE(s.removeQuantity(15) == false);
        REQUIRE(s.getCurrentQuantity() == 10);
        
        REQUIRE(s.removeQuantity(0) == false);
        REQUIRE(s.getCurrentQuantity() == 10);
    }
    
    SECTION("setQuantity sets exact quantity") {
        Stock s(product, 10);
        s.setQuantity(25);
        REQUIRE(s.getCurrentQuantity() == 25);
        
        s.setQuantity(0);
        REQUIRE(s.getCurrentQuantity() == 0);
        
        s.setQuantity(-5);
        REQUIRE(s.getCurrentQuantity() == 0);
    }
    
    SECTION("isBelowMinStock correctly identifies low stock") {
        Stock s(product, 15);
        REQUIRE(s.isBelowMinStock() == false);
        
        s.setQuantity(10);
        REQUIRE(s.isBelowMinStock() == false);
        
        s.setQuantity(5);
        REQUIRE(s.isBelowMinStock() == true);
        
        s.setQuantity(0);
        REQUIRE(s.isBelowMinStock() == true);
    }
    
    SECTION("getRecommendedOrderQuantity calculates correctly") {
        Stock s(product, 5);
        // minStock=10, current=5, deficit=5, avgDailySales=2, deliveryDays=3 -> 5 + (2*3)=11
        REQUIRE(s.getRecommendedOrderQuantity(2, 3) == 11);
        
        s.setQuantity(15);
        // current > minStock -> deficit=0, result = 0 + (2*3)=6
        REQUIRE(s.getRecommendedOrderQuantity(2, 3) == 6);
        
        s.setQuantity(10);
        REQUIRE(s.getRecommendedOrderQuantity(5, 2) == 10); // deficit=0 + 10=10
    }
    
    SECTION("Observer pattern works correctly") {
        Stock s(product, 10);
        int notificationCount = 0;
        int lastProductId = -1;
        int lastQuantity = -1;
        
        s.addObserver([&](int productId, int quantity) {
            notificationCount++;
            lastProductId = productId;
            lastQuantity = quantity;
        });
        
        s.addQuantity(5);
        REQUIRE(notificationCount == 1);
        REQUIRE(lastProductId == product->getId());
        REQUIRE(lastQuantity == 15);
        
        s.removeQuantity(3);
        REQUIRE(notificationCount == 2);
        REQUIRE(lastQuantity == 12);
    }
}
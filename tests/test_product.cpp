#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "../include/core/Product.h"

using namespace Catch::Matchers;

TEST_CASE("Product class tests", "[Product]") {
    
    SECTION("Default constructor creates valid empty product") {
        Product p;
        REQUIRE(p.getId() == 0);
        REQUIRE(p.getName().empty());
        REQUIRE(p.getArticle().empty());
        REQUIRE(p.getPurchasePrice() == 0.0);
        REQUIRE(p.getSellingPrice() == 0.0);
        REQUIRE(p.getMinStock() == 0);
    }
    
    SECTION("Parameterized constructor sets all fields correctly") {
        Product p(1, "Laptop", "LP001", "Electronics", "pcs", 500.0, 750.0, 5);
        
        REQUIRE(p.getId() == 1);
        REQUIRE(p.getName() == "Laptop");
        REQUIRE(p.getArticle() == "LP001");
        REQUIRE(p.getCategory() == "Electronics");
        REQUIRE(p.getUnit() == "pcs");
        REQUIRE(p.getPurchasePrice() == 500.0);
        REQUIRE(p.getSellingPrice() == 750.0);
        REQUIRE(p.getMinStock() == 5);
    }
    
    SECTION("Setters update values correctly") {
        Product p;
        p.setId(10);
        p.setName("Mouse");
        p.setArticle("MS002");
        p.setCategory("Accessories");
        p.setUnit("pcs");
        p.setPurchasePrice(25.5);
        p.setSellingPrice(45.0);
        p.setMinStock(10);
        
        REQUIRE(p.getId() == 10);
        REQUIRE(p.getName() == "Mouse");
        REQUIRE(p.getArticle() == "MS002");
        REQUIRE(p.getCategory() == "Accessories");
        REQUIRE(p.getUnit() == "pcs");
        REQUIRE(p.getPurchasePrice() == 25.5);
        REQUIRE(p.getSellingPrice() == 45.0);
        REQUIRE(p.getMinStock() == 10);
    }
    
    SECTION("isValid returns true for valid product") {
        Product p(1, "Valid Product", "ART001", "Category", "pcs", 100.0, 150.0, 5);
        REQUIRE(p.isValid() == true);
    }
    
    SECTION("isValid returns false for invalid product") {
        Product p1; // Default
        REQUIRE(p1.isValid() == false);
        
        Product p2(0, "", "", "", "", 0.0, 0.0, 0);
        REQUIRE(p2.isValid() == false);
        
        Product p3(1, "", "ART001", "Cat", "pcs", 100, 150, 5);
        REQUIRE(p3.isValid() == false);
    }
    
    SECTION("calculateProfitMargin returns correct percentage") {
        Product p(1, "Test", "T001", "Cat", "pcs", 100.0, 150.0, 5);
        REQUIRE(p.calculateProfitMargin() == 50.0);
        
        Product p2(2, "Test2", "T002", "Cat", "pcs", 200.0, 200.0, 5);
        REQUIRE(p2.calculateProfitMargin() == 0.0);
        
        Product p3(3, "Test3", "T003", "Cat", "pcs", 0.0, 50.0, 5);
        REQUIRE(p3.calculateProfitMargin() == 0.0);
    }
    
    SECTION("Equality operator works correctly") {
        Product p1(1, "Same", "ART1", "Cat", "pcs", 100, 150, 5);
        Product p2(1, "Same", "ART1", "Cat", "pcs", 100, 150, 5);
        Product p3(2, "Different", "ART2", "Cat", "pcs", 100, 150, 5);
        
        REQUIRE(p1 == p2);
        REQUIRE_FALSE(p1 == p3);
    }
}
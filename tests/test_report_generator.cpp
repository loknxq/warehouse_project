#include <catch2/catch_test_macros.hpp>
#include "../include/services/ReportGenerator.h"
#include "../include/core/Stock.h"
#include <memory>

TEST_CASE("ReportGenerator tests", "[ReportGenerator]") {
    
    auto product1 = std::make_shared<Product>(1, "Laptop", "LP001", "Electronics", "pcs", 500, 750, 5);
    auto product2 = std::make_shared<Product>(2, "Mouse", "MS002", "Accessories", "pcs", 25, 45, 10);
    
    SECTION("generateStockReport creates correct format") {
        std::vector<Stock> stocks;
        stocks.emplace_back(product1, 15);
        stocks.emplace_back(product2, 8);
        
        std::string report = ReportGenerator::generateStockReport(stocks, "2024-01-15");
        
        REQUIRE(report.find("STOCK REPORT FOR 2024-01-15") != std::string::npos);
        REQUIRE(report.find("Laptop") != std::string::npos);
        REQUIRE(report.find("Mouse") != std::string::npos);
        REQUIRE(report.find("15") != std::string::npos);
        REQUIRE(report.find("8") != std::string::npos);
    }
    
    SECTION("generateTopProductsReport creates correct format") {
        std::vector<std::pair<Product, int>> sales;
        sales.emplace_back(*product1, 50);
        sales.emplace_back(*product2, 30);
        
        std::string report = ReportGenerator::generateTopProductsReport(sales);
        
        REQUIRE(report.find("TOP 10 PRODUCTS") != std::string::npos);
        REQUIRE(report.find("Laptop") != std::string::npos);
        REQUIRE(report.find("50") != std::string::npos);
    }
    
    SECTION("generateOrderListReport creates correct format") {
        std::vector<std::pair<Product, int>> toOrder;
        toOrder.emplace_back(*product1, 10);
        toOrder.emplace_back(*product2, 5);
        
        std::string report = ReportGenerator::generateOrderListReport(toOrder);
        
        REQUIRE(report.find("PRODUCTS TO ORDER") != std::string::npos);
        REQUIRE(report.find("Laptop") != std::string::npos);
        REQUIRE(report.find("10") != std::string::npos);
    }
    
    SECTION("addFilter decorates report correctly") {
        std::string baseReport = "Base report content";
        std::string filtered = ReportGenerator::addFilter(baseReport, "Electronics");
        
        REQUIRE(filtered.find("FILTERED(Electronics)") != std::string::npos);
        REQUIRE(filtered.find("Base report content") != std::string::npos);
    }
    
    SECTION("addValueColumn decorates report correctly") {
        std::vector<Stock> stocks;
        stocks.emplace_back(product1, 15);
        
        std::string baseReport = "Base report";
        std::string decorated = ReportGenerator::addValueColumn(baseReport, stocks);
        
        REQUIRE(decorated.find("[Value column added]") != std::string::npos);
        REQUIRE(decorated.find("Base report") != std::string::npos);
    }
    
    SECTION("generateMovementReport returns non-empty string") {
        std::string report = ReportGenerator::generateMovementReport("2024-01-01", "2024-01-31");
        REQUIRE_FALSE(report.empty());
        REQUIRE(report.find("MOVEMENT REPORT") != std::string::npos);
    }
}
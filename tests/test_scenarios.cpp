#include <catch2/catch_test_macros.hpp>
#include "../include/core/Product.h"
#include "../include/core/Stock.h"
#include "../include/core/User.h"
#include "../include/core/Supplier.h"
#include "../include/documents/IncomingOperation.h"
#include "../include/documents/OutgoingOperation.h"
#include "../include/services/Logger.h"
#include "../include/services/OrderCalculator.h"
#include "../include/services/ReportGenerator.h"
#include "../include/strategies/AverageSalesStrategy.h"
#include <memory>
#include <vector>
#include <iostream>


TEST_CASE("Scenario 1: Complete product lifecycle", "[Scenario]") {
    
    auto product = std::make_shared<Product>(1, "Test Laptop", "LP001", 
                                               "Electronics", "pcs", 500.0, 750.0, 5);
    REQUIRE(product->isValid() == true);
    REQUIRE(product->calculateProfitMargin() == 50.0);
    
    Stock stock(product, 0);
    REQUIRE(stock.getCurrentQuantity() == 0);
    REQUIRE(stock.isBelowMinStock() == true);
    
    auto supplier = std::make_shared<Supplier>(1, "Tech Supplier", "Contact Person", "+7-999-123-4567", "tech@supplier.com");
    IncomingOperation incoming(1, "IN-DOC-001", supplier, "INV-001");
    incoming.addItem(product, 20, 480.0);
    REQUIRE(incoming.validate() == true);
    
    stock.addQuantity(20);
    REQUIRE(stock.getCurrentQuantity() == 20);
    REQUIRE(stock.isBelowMinStock() == false);
    
    OutgoingOperation outgoing(1, "OUT-DOC-001", "Customer ABC", "ORD-001");
    outgoing.addItem(product, 10, 750.0);
    REQUIRE(outgoing.validate() == true);
    
    bool removalSuccess = stock.removeQuantity(10);
    REQUIRE(removalSuccess == true);
    REQUIRE(stock.getCurrentQuantity() == 10);
    REQUIRE(stock.isBelowMinStock() == false);
    
    stock.removeQuantity(6);
    REQUIRE(stock.getCurrentQuantity() == 4);
    REQUIRE(stock.isBelowMinStock() == true);
    
    OrderCalculator calculator(std::make_shared<AverageSalesStrategy>());
    int recommendedQty = calculator.calculateRecommendedQuantity(
        stock.getCurrentQuantity(), 
        product->getMinStock(), 
        2, // Среднедневные продажи
        3  // Дни доставки
    );
    REQUIRE(recommendedQty == 7);
    
    Logger* logger = Logger::getInstance();
    logger->clearLogs();
    logger->log(1, "SCENARIO_COMPLETE", product->getId());
    REQUIRE(logger->getLogCount() == 1);
}

TEST_CASE("Scenario 2: Multiple products management", "[Scenario]") {
    
    std::vector<Stock> warehouse;
    
    auto p1 = std::make_shared<Product>(1, "Laptop", "LP001", "Electronics", "pcs", 500, 750, 5);
    auto p2 = std::make_shared<Product>(2, "Mouse", "MS002", "Accessories", "pcs", 25, 45, 10);
    auto p3 = std::make_shared<Product>(3, "Keyboard", "KB003", "Accessories", "pcs", 60, 90, 8);
    
    warehouse.emplace_back(p1, 15);
    warehouse.emplace_back(p2, 3);
    warehouse.emplace_back(p3, 12);
    
    std::vector<int> productsToOrder;
    for (const auto& stock : warehouse) {
        if (stock.isBelowMinStock()) {
            productsToOrder.push_back(stock.getProduct()->getId());
        }
    }
    
    REQUIRE(productsToOrder.size() == 1);
    REQUIRE(productsToOrder[0] == 2);
    
    Logger* logger = Logger::getInstance();
    logger->clearLogs();
    logger->log(1, "MULTIPLE_PRODUCTS_CHECK", 0);
    REQUIRE(logger->getLogCount() == 1);
}
TEST_CASE("Scenario 3: Authentication and permissions", "[Scenario]") {
    
    User admin(1, "admin", "admin123", UserRole::ADMIN);
    User storekeeper(2, "store", "store123", UserRole::STOREKEEPER);
    User manager(3, "manager", "manager123", UserRole::MANAGER);
    
    REQUIRE(admin.authenticate("admin123") == true);
    REQUIRE(storekeeper.authenticate("store123") == true);
    REQUIRE(manager.authenticate("manager123") == true);
    REQUIRE(admin.authenticate("wrong") == false);
    
    REQUIRE(storekeeper.hasPermission(UserRole::STOREKEEPER) == true);
    REQUIRE(storekeeper.hasPermission(UserRole::MANAGER) == false);
    REQUIRE(storekeeper.hasPermission(UserRole::WAREHOUSE_HEAD) == false);
    
    REQUIRE(manager.hasPermission(UserRole::STOREKEEPER) == true);
    REQUIRE(manager.hasPermission(UserRole::MANAGER) == true);
    REQUIRE(manager.hasPermission(UserRole::WAREHOUSE_HEAD) == false);
    
    REQUIRE(admin.hasPermission(UserRole::STOREKEEPER) == true);
    REQUIRE(admin.hasPermission(UserRole::MANAGER) == true);
    REQUIRE(admin.hasPermission(UserRole::WAREHOUSE_HEAD) == true);
    REQUIRE(admin.hasPermission(UserRole::ADMIN) == true);
    
    Logger* logger = Logger::getInstance();
    logger->clearLogs();
    logger->log(admin.getId(), "LOGIN", 0);
    logger->log(storekeeper.getId(), "LOGIN", 0);
    
    REQUIRE(logger->getLogCount() == 2);
}

TEST_CASE("Scenario 4: Incoming and outgoing operations", "[Scenario]") {
    
    auto product = std::make_shared<Product>(1, "Product X", "X001", "Category", "pcs", 100, 150, 10);
    auto supplier = std::make_shared<Supplier>(1, "Supplier Y", "Contact Person", "+7-999-123-4567", "supplier@test.com");
    Stock stock(product, 5);
    
    IncomingOperation incoming(1, "IN-001", supplier, "INV-001");
    incoming.addItem(product, 15, 95.0);
    REQUIRE(incoming.validate() == true);
    REQUIRE(incoming.getTotalValue() == 1425.0);
    REQUIRE(incoming.getTotalQuantity() == 15);
    
    stock.addQuantity(15);
    REQUIRE(stock.getCurrentQuantity() == 20);
    
    OutgoingOperation outgoing(1, "OUT-001", "Customer Z", "ORD-001");
    outgoing.addItem(product, 8, 145.0);
    REQUIRE(outgoing.validate() == true);
    REQUIRE(outgoing.getTotalValue() == 1160.0);
    REQUIRE(outgoing.getTotalQuantity() == 8);
    
    bool success = stock.removeQuantity(8);
    REQUIRE(success == true);
    REQUIRE(stock.getCurrentQuantity() == 12);
    
    success = stock.removeQuantity(20);
    REQUIRE(success == false);
    REQUIRE(stock.getCurrentQuantity() == 12);
}

TEST_CASE("Scenario 5: Observer pattern notifications", "[Scenario]") {
    
    auto product = std::make_shared<Product>(1, "Monitor", "MON001", "Electronics", "pcs", 200, 300, 3);
    Stock stock(product, 10);
    
    int notificationCount = 0;
    std::vector<int> notifiedQuantities;
    
    stock.addObserver([&](int productId, int quantity) {
        notificationCount++;
        notifiedQuantities.push_back(quantity);
    });
    
    stock.addQuantity(5);
    REQUIRE(notificationCount == 1);
    REQUIRE(notifiedQuantities.back() == 15);
    
    stock.removeQuantity(3);
    REQUIRE(notificationCount == 2);
    REQUIRE(notifiedQuantities.back() == 12);
    
    stock.setQuantity(0);
    REQUIRE(notificationCount == 3);
    REQUIRE(notifiedQuantities.back() == 0);
    REQUIRE(stock.isBelowMinStock() == true);
}

TEST_CASE("Scenario 6: Report generation", "[Scenario]") {
    
    auto p1 = std::make_shared<Product>(1, "Product A", "A001", "Cat1", "pcs", 100, 150, 5);
    auto p2 = std::make_shared<Product>(2, "Product B", "B002", "Cat2", "pcs", 50, 80, 10);
    
    std::vector<Stock> stocks;
    stocks.emplace_back(p1, 25);
    stocks.emplace_back(p2, 3);
    
    std::string stockReport = ReportGenerator::generateStockReport(stocks, "2024-01-15");
    REQUIRE_FALSE(stockReport.empty());
    REQUIRE(stockReport.find("Product A") != std::string::npos);
    REQUIRE(stockReport.find("Product B") != std::string::npos);
    
    std::vector<std::pair<Product, int>> topSales;
    topSales.emplace_back(*p1, 100);
    topSales.emplace_back(*p2, 50);
    
    std::string topReport = ReportGenerator::generateTopProductsReport(topSales);
    REQUIRE(topReport.find("Product A") != std::string::npos);
    REQUIRE(topReport.find("100") != std::string::npos);
    
    std::vector<std::pair<Product, int>> toOrder;
    toOrder.emplace_back(*p2, 10);
    
    std::string orderReport = ReportGenerator::generateOrderListReport(toOrder);
    REQUIRE(orderReport.find("Product B") != std::string::npos);
    REQUIRE(orderReport.find("10") != std::string::npos);
}

TEST_CASE("Scenario 7: Strategy pattern for order calculation", "[Scenario]") {
    
    auto strategy = std::make_shared<AverageSalesStrategy>();
    OrderCalculator calculator(strategy);
    
    struct TestCase {
        int currentStock;
        int minStock;
        int avgDailySales;
        int deliveryDays;
        int expected;
    };
    
    std::vector<TestCase> testCases = {
        {10, 20, 2, 5, 20},
        {25, 20, 3, 7, 21},
        {0, 10, 5, 2, 20},
        {8, 8, 4, 3, 12},
        {5, 15, 1, 10, 20}
    };
    
    for (const auto& tc : testCases) {
        int result = calculator.calculateRecommendedQuantity(
            tc.currentStock, tc.minStock, tc.avgDailySales, tc.deliveryDays);
        REQUIRE(result == tc.expected);
    }
    
    auto newStrategy = std::make_shared<AverageSalesStrategy>();
    calculator.setStrategy(newStrategy);
    REQUIRE(calculator.getCurrentStrategyName() == "Average Sales Strategy (30 days)");
}

TEST_CASE("Scenario 8: Document validation", "[Scenario]") {
    
    auto product = std::make_shared<Product>(1, "Test", "T001", "Cat", "pcs", 100, 150, 5);
    auto supplier = std::make_shared<Supplier>(1, "Supplier", "Contact", "+7-999-123-4567", "email@test.com");
    
    SECTION("Valid incoming document") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product, 10, 95.0);
        REQUIRE(op.validate() == true);
        REQUIRE(op.saveToDatabase() == true);
    }
    
    SECTION("Invalid incoming document - no items") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        REQUIRE(op.validate() == false);
    }
    
    SECTION("Invalid incoming document - negative quantity") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product, -5, 95.0);
        REQUIRE(op.validate() == false);
    }
    
    SECTION("Valid outgoing document") {
        OutgoingOperation op(1, "DOC001", "Customer", "ORD001");
        op.addItem(product, 5, 145.0);
        REQUIRE(op.validate() == true);
        REQUIRE(op.saveToDatabase() == true);
    }
    
    SECTION("Invalid outgoing document - empty customer") {
        OutgoingOperation op(1, "DOC001", "", "ORD001");
        op.addItem(product, 5, 145.0);
        REQUIRE(op.validate() == false);
    }
}

TEST_CASE("Scenario 9: System logging", "[Scenario]") {
    
    Logger* logger = Logger::getInstance();
    logger->clearLogs();
    
    logger->log(1, "PRODUCT_CREATED", 101);
    logger->log(1, "PRODUCT_UPDATED", 101);
    logger->log(2, "STOCK_UPDATED", 101);
    logger->log(3, "ORDER_CREATED", 201);
    logger->log(1, "PRODUCT_DELETED", 101);
    
    REQUIRE(logger->getLogCount() == 5);
    
    auto user1Logs = logger->getLogsByUser(1);
    REQUIRE(user1Logs.size() == 3);
    
    auto user3Logs = logger->getLogsByUser(3);
    REQUIRE(user3Logs.size() == 1);
    REQUIRE(user3Logs[0].operationType == "ORDER_CREATED");
    
    logger->clearLogs();
    REQUIRE(logger->getLogCount() == 0);
}

TEST_CASE("Scenario 10: Complete warehouse workflow", "[Scenario]") {
    
    Logger* logger = Logger::getInstance();
    logger->clearLogs();
    
    auto laptop = std::make_shared<Product>(1, "Gaming Laptop", "GL001", "Electronics", "pcs", 800, 1200, 5);
    auto mouse = std::make_shared<Product>(2, "Wireless Mouse", "WM002", "Accessories", "pcs", 30, 50, 15);
    
    REQUIRE(laptop->isValid() == true);
    REQUIRE(mouse->isValid() == true);
    
    logger->log(4, "PRODUCTS_CREATED", 0);
    
    Stock laptopStock(laptop, 8);
    Stock mouseStock(mouse, 10);
    
    REQUIRE(laptopStock.getCurrentQuantity() == 8);
    REQUIRE(mouseStock.getCurrentQuantity() == 10);
    
    auto supplier = std::make_shared<Supplier>(1, "TechDistro", "Contact Person", "+7-999-123-4567", "info@techdistro.com");
    IncomingOperation incoming(1, "IN-2024-001", supplier, "INV-789");
    incoming.addItem(laptop, 5, 780.0);
    incoming.addItem(mouse, 20, 28.0);
    
    REQUIRE(incoming.validate() == true);
    REQUIRE(incoming.getTotalValue() == (5*780 + 20*28));
    
    laptopStock.addQuantity(5);
    mouseStock.addQuantity(20);
    
    REQUIRE(laptopStock.getCurrentQuantity() == 13);
    REQUIRE(mouseStock.getCurrentQuantity() == 30);
    
    logger->log(1, "INCOMING_PROCESSED", incoming.getId());
    
    OutgoingOperation outgoing(1, "OUT-2024-001", "Corporate Client", "PO-456");
    outgoing.addItem(laptop, 3, 1199.0);
    outgoing.addItem(mouse, 10, 49.0);
    
    REQUIRE(outgoing.validate() == true);
    
    laptopStock.removeQuantity(3);
    mouseStock.removeQuantity(10);
    
    REQUIRE(laptopStock.getCurrentQuantity() == 10);
    REQUIRE(mouseStock.getCurrentQuantity() == 20);
    
    logger->log(1, "OUTGOING_PROCESSED", outgoing.getId());
    
    REQUIRE(laptopStock.isBelowMinStock() == false);
    REQUIRE(mouseStock.isBelowMinStock() == false);
    
    mouseStock.removeQuantity(8);
    REQUIRE(mouseStock.getCurrentQuantity() == 12);
    REQUIRE(mouseStock.isBelowMinStock() == true);
    
    OrderCalculator calculator(std::make_shared<AverageSalesStrategy>());
    int mouseReorderQty = calculator.calculateRecommendedQuantity(
        mouseStock.getCurrentQuantity(),
        mouse->getMinStock(),
        3,
        4
    );
    
    REQUIRE(mouseReorderQty == 15);
    
    logger->log(3, "ORDER_RECOMMENDATION", mouse->getId());
    
    std::vector<Stock> stocks = {laptopStock, mouseStock};
    std::string report = ReportGenerator::generateStockReport(stocks, "2024-01-15");
    REQUIRE_FALSE(report.empty());
    
    REQUIRE(logger->getLogCount() == 4);
}

TEST_CASE("Scenario 11: Supplier management", "[Scenario]") {
    
    auto s1 = std::make_shared<Supplier>(1, "Supplier A", "Contact A", "+7-111-111-1111", "a@test.com");
    auto s2 = std::make_shared<Supplier>(2, "Supplier B", "Contact B", "+7-222-222-2222", "b@test.com");
    
    REQUIRE(s1->isValid() == true);
    REQUIRE(s2->isValid() == true);
    REQUIRE_FALSE((*s1) == (*s2));
    
    s1->setName("Updated Supplier A");
    s1->setPhone("+7-999-999-9999");
    
    REQUIRE(s1->getName() == "Updated Supplier A");
    REQUIRE(s1->getPhone() == "+7-999-999-9999");
}
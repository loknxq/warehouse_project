#include <catch2/catch_test_macros.hpp>
#include "../include/documents/OutgoingOperation.h"
#include <memory>

TEST_CASE("OutgoingOperation tests", "[OutgoingOperation]") {
    
    auto product1 = std::make_shared<Product>(1, "Product A", "A001", "Cat1", "pcs", 100, 150, 10);
    auto product2 = std::make_shared<Product>(2, "Product B", "B002", "Cat2", "pcs", 50, 80, 5);
    
    SECTION("Default constructor") {
        OutgoingOperation op;
        REQUIRE(op.getId() == 0);
        REQUIRE(op.getDocumentNumber().empty());
        REQUIRE(op.getCustomerName().empty());
        REQUIRE(op.getCustomerOrderNumber().empty());
        REQUIRE(op.getItems().empty());
    }
    
    SECTION("Parameterized constructor") {
        OutgoingOperation op(1, "DOC001", "Customer ABC", "ORD123");
        REQUIRE(op.getId() == 1);
        REQUIRE(op.getDocumentNumber() == "DOC001");
        REQUIRE(op.getCustomerName() == "Customer ABC");
        REQUIRE(op.getCustomerOrderNumber() == "ORD123");
    }
    
    SECTION("addItem adds items correctly") {
        OutgoingOperation op(1, "DOC001", "Customer", "ORD123");
        op.addItem(product1, 5, 150.0);
        op.addItem(product2, 3, 80.0);
        
        auto items = op.getItems();
        REQUIRE(items.size() == 2);
        REQUIRE(items[0].product == product1);
        REQUIRE(items[0].quantity == 5);
        REQUIRE(items[0].sellingPrice == 150.0);
        REQUIRE(items[1].product == product2);
        REQUIRE(items[1].quantity == 3);
    }
    
    SECTION("removeItem removes correct items") {
        OutgoingOperation op(1, "DOC001", "Customer", "ORD123");
        op.addItem(product1, 5, 150.0);
        op.addItem(product2, 3, 80.0);
        
        op.removeItem(0);
        auto items = op.getItems();
        REQUIRE(items.size() == 1);
        REQUIRE(items[0].product == product2);
    }
    
    SECTION("clearItems removes all items") {
        OutgoingOperation op(1, "DOC001", "Customer", "ORD123");
        op.addItem(product1, 5, 150.0);
        op.addItem(product2, 3, 80.0);
        
        op.clearItems();
        REQUIRE(op.getItems().empty());
    }
    
    SECTION("getTotalValue calculates correct total") {
        OutgoingOperation op(1, "DOC001", "Customer", "ORD123");
        op.addItem(product1, 2, 150.0);
        op.addItem(product2, 3, 80.0);
        
        REQUIRE(op.getTotalValue() == 540.0); // 300 + 240
        
        op.addItem(product1, 1, 150.0);
        REQUIRE(op.getTotalValue() == 690.0);
    }
    
    SECTION("getTotalQuantity returns sum of quantities") {
        OutgoingOperation op(1, "DOC001", "Customer", "ORD123");
        op.addItem(product1, 5, 150.0);
        op.addItem(product2, 3, 80.0);
        op.addItem(product1, 2, 150.0);
        
        REQUIRE(op.getTotalQuantity() == 10);
    }
    
    SECTION("validate returns true for valid operation") {
        OutgoingOperation op(1, "DOC001", "Customer ABC", "ORD123");
        op.addItem(product1, 5, 150.0);
        op.addItem(product2, 3, 80.0);
        
        REQUIRE(op.validate() == true);
    }
    
    SECTION("validate returns false for invalid operation") {
        OutgoingOperation op;
        REQUIRE(op.validate() == false);
        
        OutgoingOperation op2(0, "", "", "");
        REQUIRE(op2.validate() == false);
        
        OutgoingOperation op3(1, "DOC001", "Customer", "ORD123");
        REQUIRE(op3.validate() == false); // No items
        
        OutgoingOperation op4(1, "DOC001", "Customer", "ORD123");
        op4.addItem(product1, -5, 150.0); // Negative quantity
        REQUIRE(op4.validate() == false);
        
        OutgoingOperation op5(1, "DOC001", "Customer", "ORD123");
        op5.addItem(product1, 5, -10.0); // Negative price
        REQUIRE(op5.validate() == false);
    }
    
    SECTION("getType returns correct type") {
        OutgoingOperation op;
        REQUIRE(op.getType() == "OUTGOING");
    }
}
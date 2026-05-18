#include <catch2/catch_test_macros.hpp>
#include "../include/documents/IncomingOperation.h"
#include "../include/core/Supplier.h"
#include <memory>

TEST_CASE("IncomingOperation tests", "[IncomingOperation]") {
    
    auto product1 = std::make_shared<Product>(1, "Product A", "A001", "Cat1", "pcs", 100, 150, 10);
    auto product2 = std::make_shared<Product>(2, "Product B", "B002", "Cat2", "pcs", 50, 80, 5);
    auto supplier = std::make_shared<Supplier>(1, "Test Supplier", "Contact Person", "+7-999-123-4567", "test@supplier.com");
    
    SECTION("Default constructor") {
        IncomingOperation op;
        REQUIRE(op.getId() == 0);
        REQUIRE(op.getDocumentNumber().empty());
        REQUIRE(op.getSupplier() == nullptr);
        REQUIRE(op.getItems().empty());
    }
    
    SECTION("Parameterized constructor") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        REQUIRE(op.getId() == 1);
        REQUIRE(op.getDocumentNumber() == "DOC001");
        REQUIRE(op.getSupplier() == supplier);
        REQUIRE(op.getInvoiceNumber() == "INV001");
    }
    
    SECTION("addItem adds items correctly") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product1, 10, 95.0);
        op.addItem(product2, 20, 48.0);
        
        auto items = op.getItems();
        REQUIRE(items.size() == 2);
        REQUIRE(items[0].product == product1);
        REQUIRE(items[0].quantity == 10);
        REQUIRE(items[0].actualPrice == 95.0);
        REQUIRE(items[1].product == product2);
        REQUIRE(items[1].quantity == 20);
    }
    
    SECTION("removeItem removes correct items") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product1, 10, 95.0);
        op.addItem(product2, 20, 48.0);
        
        op.removeItem(0);
        auto items = op.getItems();
        REQUIRE(items.size() == 1);
        REQUIRE(items[0].product == product2);
        
        op.removeItem(5); 
        REQUIRE(items.size() == 1);
    }
    
    SECTION("clearItems removes all items") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product1, 10, 95.0);
        op.addItem(product2, 20, 48.0);
        
        op.clearItems();
        REQUIRE(op.getItems().empty());
    }
    
    SECTION("getTotalValue calculates correct total") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product1, 10, 100.0);
        op.addItem(product2, 5, 50.0);
        
        REQUIRE(op.getTotalValue() == 1250.0);
        
        op.addItem(product1, 2, 100.0);
        REQUIRE(op.getTotalValue() == 1450.0);
    }
    
    SECTION("getTotalQuantity returns sum of quantities") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product1, 10, 100.0);
        op.addItem(product2, 5, 50.0);
        op.addItem(product1, 3, 100.0);
        
        REQUIRE(op.getTotalQuantity() == 18);
    }
    
    SECTION("validate returns true for valid operation") {
        IncomingOperation op(1, "DOC001", supplier, "INV001");
        op.addItem(product1, 10, 100.0);
        op.addItem(product2, 5, 50.0);
        
        REQUIRE(op.validate() == true);
    }
    
    SECTION("validate returns false for invalid operation") {
        IncomingOperation op;
        REQUIRE(op.validate() == false);
        
        IncomingOperation op2(0, "", nullptr, "");
        REQUIRE(op2.validate() == false);
        
        IncomingOperation op3(1, "DOC001", supplier, "INV001");
        REQUIRE(op3.validate() == false); 
        
        IncomingOperation op4(1, "DOC001", supplier, "INV001");
        op4.addItem(product1, -5, 100.0); 
        REQUIRE(op4.validate() == false);
        
        IncomingOperation op5(1, "DOC001", supplier, "INV001");
        op5.addItem(product1, 10, -10.0); 
        REQUIRE(op5.validate() == false);
    }
    
    SECTION("getType returns correct type") {
        IncomingOperation op;
        REQUIRE(op.getType() == "INCOMING");
    }
}
// warehouse_project/tests/test_supplier.cpp
#include <catch2/catch_test_macros.hpp>
#include "../include/core/Supplier.h"

TEST_CASE("Supplier class tests", "[Supplier]") {
    
    SECTION("Default constructor") {
        Supplier s;
        REQUIRE(s.getId() == 0);
        REQUIRE(s.getName().empty());
        REQUIRE(s.getContactPerson().empty());
        REQUIRE(s.getPhone().empty());
        REQUIRE(s.getEmail().empty());
    }
    
    SECTION("Parameterized constructor") {
        Supplier s(1, "TechDistro", "John Smith", "+7-999-123-4567", "john@techdistro.com");
        REQUIRE(s.getId() == 1);
        REQUIRE(s.getName() == "TechDistro");
        REQUIRE(s.getContactPerson() == "John Smith");
        REQUIRE(s.getPhone() == "+7-999-123-4567");
        REQUIRE(s.getEmail() == "john@techdistro.com");
    }
    
    SECTION("Setters update values") {
        Supplier s;
        s.setId(5);
        s.setName("New Supplier");
        s.setContactPerson("Jane Doe");
        s.setPhone("+7-888-555-1234");
        s.setEmail("jane@newsupplier.com");
        
        REQUIRE(s.getId() == 5);
        REQUIRE(s.getName() == "New Supplier");
        REQUIRE(s.getContactPerson() == "Jane Doe");
        REQUIRE(s.getPhone() == "+7-888-555-1234");
        REQUIRE(s.getEmail() == "jane@newsupplier.com");
    }
    
    SECTION("isValid returns true for valid supplier") {
        Supplier s(1, "Valid", "Contact", "123456", "email@test.com");
        REQUIRE(s.isValid() == true);
    }
    
    SECTION("isValid returns false for invalid supplier") {
        Supplier s1;
        REQUIRE(s1.isValid() == false);
        
        Supplier s2(0, "", "", "", "");
        REQUIRE(s2.isValid() == false);
        
        Supplier s3(1, "", "Contact", "123", "email");
        REQUIRE(s3.isValid() == false);
    }
    
    SECTION("Equality operator works") {
        Supplier s1(1, "Name1", "Contact1", "111", "e1");
        Supplier s2(1, "Name1", "Contact1", "111", "e1");
        Supplier s3(2, "Name2", "Contact2", "222", "e2");
        
        REQUIRE(s1 == s2);
        REQUIRE_FALSE(s1 == s3);
    }
}
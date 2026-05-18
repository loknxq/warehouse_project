#include <catch2/catch_test_macros.hpp>
#include "../include/core/User.h"

TEST_CASE("User class tests", "[User]") {
    
    SECTION("Default constructor") {
        User u;
        REQUIRE(u.getId() == 0);
        REQUIRE(u.getLogin().empty());
        REQUIRE(u.getRole() == UserRole::STOREKEEPER);
    }
    
    SECTION("Parameterized constructor") {
        User u(1, "john_doe", "password123", UserRole::ADMIN);
        REQUIRE(u.getId() == 1);
        REQUIRE(u.getLogin() == "john_doe");
        REQUIRE(u.getRole() == UserRole::ADMIN);
        REQUIRE(u.getRoleString() == "ADMIN");
    }
    
    SECTION("Authentication works correctly") {
        User u(1, "test_user", "secret123", UserRole::MANAGER);
        REQUIRE(u.authenticate("secret123") == true);
        REQUIRE(u.authenticate("wrongpassword") == false);
        REQUIRE(u.authenticate("") == false);
    }
    
    SECTION("Password hashing produces consistent results") {
        User u1(1, "user1", "mypass", UserRole::STOREKEEPER);
        User u2(2, "user2", "mypass", UserRole::MANAGER);
        
        REQUIRE(u1.authenticate("mypass") == true);
        REQUIRE(u2.authenticate("mypass") == true);
        REQUIRE(u1.authenticate("mypass") == u2.authenticate("mypass"));
    }
    
    SECTION("hasPermission checks role hierarchy correctly") {
        User storekeeper(1, "store", "pass", UserRole::STOREKEEPER);
        User manager(2, "manager", "pass", UserRole::MANAGER);
        User head(3, "head", "pass", UserRole::WAREHOUSE_HEAD);
        User admin(4, "admin", "pass", UserRole::ADMIN);
        
        REQUIRE(storekeeper.hasPermission(UserRole::STOREKEEPER) == true);
        REQUIRE(storekeeper.hasPermission(UserRole::MANAGER) == false);
        REQUIRE(storekeeper.hasPermission(UserRole::WAREHOUSE_HEAD) == false);
        REQUIRE(storekeeper.hasPermission(UserRole::ADMIN) == false);
        
        REQUIRE(manager.hasPermission(UserRole::STOREKEEPER) == true);
        REQUIRE(manager.hasPermission(UserRole::MANAGER) == true);
        REQUIRE(manager.hasPermission(UserRole::WAREHOUSE_HEAD) == false);
        REQUIRE(manager.hasPermission(UserRole::ADMIN) == false);
        
        REQUIRE(head.hasPermission(UserRole::STOREKEEPER) == true);
        REQUIRE(head.hasPermission(UserRole::MANAGER) == true);
        REQUIRE(head.hasPermission(UserRole::WAREHOUSE_HEAD) == true);
        REQUIRE(head.hasPermission(UserRole::ADMIN) == false);
        
        REQUIRE(admin.hasPermission(UserRole::STOREKEEPER) == true);
        REQUIRE(admin.hasPermission(UserRole::MANAGER) == true);
        REQUIRE(admin.hasPermission(UserRole::WAREHOUSE_HEAD) == true);
        REQUIRE(admin.hasPermission(UserRole::ADMIN) == true);
    }
    
    SECTION("getRoleString returns correct string for each role") {
        User u1(1, "u1", "p", UserRole::STOREKEEPER);
        REQUIRE(u1.getRoleString() == "STOREKEEPER");
        
        User u2(2, "u2", "p", UserRole::MANAGER);
        REQUIRE(u2.getRoleString() == "MANAGER");
        
        User u3(3, "u3", "p", UserRole::WAREHOUSE_HEAD);
        REQUIRE(u3.getRoleString() == "WAREHOUSE_HEAD");
        
        User u4(4, "u4", "p", UserRole::ADMIN);
        REQUIRE(u4.getRoleString() == "ADMIN");
    }
    
    SECTION("Equality operator works") {
        User u1(1, "user1", "pass", UserRole::STOREKEEPER);
        User u2(1, "user1", "pass", UserRole::STOREKEEPER);
        User u3(2, "user2", "pass", UserRole::MANAGER);
        
        REQUIRE(u1 == u2);
        REQUIRE_FALSE(u1 == u3);
    }
}

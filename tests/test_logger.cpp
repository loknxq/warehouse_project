// warehouse_project/tests/test_logger.cpp
#include <catch2/catch_test_macros.hpp>
#include "../include/services/Logger.h"

TEST_CASE("Logger singleton tests", "[Logger]") {
    
    SECTION("getInstance returns same instance") {
        Logger* logger1 = Logger::getInstance();
        Logger* logger2 = Logger::getInstance();
        
        REQUIRE(logger1 == logger2);
    }
    
    SECTION("log adds entries correctly") {
        Logger* logger = Logger::getInstance();
        logger->clearLogs();
        
        logger->log(1, "CREATE_PRODUCT", 100);
        logger->log(2, "UPDATE_STOCK", 101);
        logger->log(1, "DELETE_PRODUCT", 102);
        
        REQUIRE(logger->getLogCount() == 3);
    }
    
    SECTION("getLogsByUser returns correct entries") {
        Logger* logger = Logger::getInstance();
        logger->clearLogs();
        
        logger->log(1, "OP1", 1);
        logger->log(2, "OP2", 2);
        logger->log(1, "OP3", 3);
        logger->log(3, "OP4", 4);
        
        auto user1Logs = logger->getLogsByUser(1);
        REQUIRE(user1Logs.size() == 2);
        REQUIRE(user1Logs[0].userId == 1);
        REQUIRE(user1Logs[1].userId == 1);
        
        auto user2Logs = logger->getLogsByUser(2);
        REQUIRE(user2Logs.size() == 1);
        
        auto user4Logs = logger->getLogsByUser(4);
        REQUIRE(user4Logs.empty());
    }
    
    SECTION("clearLogs removes all entries") {
        Logger* logger = Logger::getInstance();
        logger->clearLogs();
        
        logger->log(1, "TEST", 1);
        logger->log(2, "TEST", 2);
        REQUIRE(logger->getLogCount() == 2);
        
        logger->clearLogs();
        REQUIRE(logger->getLogCount() == 0);
    }
    
    SECTION("LogEntry toString works") {
        Logger* logger = Logger::getInstance();
        logger->clearLogs();
        
        logger->log(1, "TEST_OP", 42);
        auto logs = logger->getLogs();
        REQUIRE(logs.size() == 1);
        
        std::string logStr = logs[0].toString();
        REQUIRE(logStr.find("TEST_OP") != std::string::npos);
        REQUIRE(logStr.find("42") != std::string::npos);
    }
}
// warehouse_project/src/main.cpp
#include <iostream>
#include "../include/services/Logger.h"

int main() {
    std::cout << "Warehouse Management System v1.0\n";
    std::cout << "Main application entry point\n";
    
    Logger* logger = Logger::getInstance();
    logger->log(1, "APP_START", 0);
    
    std::cout << "Application started successfully.\n";
    
    return 0;
}
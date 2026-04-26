#include "services/Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger* Logger::instance = nullptr;

Logger::Logger() {
    logFile.open("warehouse.log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Не удалось открыть файл логов" << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

void Logger::log(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    
    if (logFile.is_open()) {
        logFile << std::ctime(&now_time) << " - " << message << std::endl;
    }
    std::cout << "[LOG] " << message << std::endl;
}

void Logger::log(const std::string& user, const std::string& action, const std::string& object) {
    std::string message = "Пользователь " + user + " выполнил действие " + action + " над объектом " + object;
    log(message);
}
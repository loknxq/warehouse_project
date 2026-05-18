#include "../../include/services/Logger.h"
#include <iostream>
#include <sstream>

LogEntry::LogEntry(int uid, const std::string& opType, int oid)
    : userId(uid), timestamp(std::time(nullptr)), operationType(opType), objectId(oid) {}

std::string LogEntry::toString() const {
    std::stringstream ss;
    ss << "[" << timestamp << "] User:" << userId 
       << " Op:" << operationType << " Obj:" << objectId;
    return ss.str();
}

Logger* Logger::instance = nullptr;

Logger::Logger() {}

Logger::~Logger() {}

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

void Logger::log(int userId, const std::string& operationType, int objectId) {
    logs.emplace_back(userId, operationType, objectId);
}

std::vector<LogEntry> Logger::getLogs() const { return logs; }

std::vector<LogEntry> Logger::getLogsByUser(int userId) const {
    std::vector<LogEntry> result;
    for (const auto& log : logs) {
        if (log.userId == userId) {
            result.push_back(log);
        }
    }
    return result;
}

void Logger::clearLogs() { logs.clear(); }

int Logger::getLogCount() const { return static_cast<int>(logs.size()); }
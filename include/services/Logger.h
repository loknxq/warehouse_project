// warehouse_project/include/services/Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <ctime>

struct LogEntry {
    int userId;
    std::time_t timestamp;
    std::string operationType;
    int objectId;
    
    LogEntry(int uid, const std::string& opType, int oid);
    std::string toString() const;
};

class Logger {
private:
    static Logger* instance;
    std::vector<LogEntry> logs;
    
    Logger();
    ~Logger();

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    static Logger* getInstance();
    
    void log(int userId, const std::string& operationType, int objectId);
    std::vector<LogEntry> getLogs() const;
    std::vector<LogEntry> getLogsByUser(int userId) const;
    void clearLogs();
    int getLogCount() const;
};

#endif
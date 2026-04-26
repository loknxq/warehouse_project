#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
private:
    static Logger* instance;
    std::ofstream logFile;

    Logger();
    ~Logger();

public:
    static Logger* getInstance();
    void log(const std::string& message);
    void log(const std::string& user, const std::string& action, const std::string& object);
};

#endif
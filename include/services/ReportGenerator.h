#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>

class Report {
public:
    virtual ~Report() {}
    virtual std::string generate() = 0;
};

class StockReport : public Report {
public:
    std::string generate() override;
};

class MovementReport : public Report {
public:
    std::string generate() override;
};

class ReportDecorator : public Report {
protected:
    Report* wrapped;
public:
    ReportDecorator(Report* report);
    virtual ~ReportDecorator();
};

class FilterDecorator : public ReportDecorator {
private:
    std::string category;
public:
    FilterDecorator(Report* report, std::string category);
    std::string generate() override;
};

class ValueDecorator : public ReportDecorator {
public:
    ValueDecorator(Report* report);
    std::string generate() override;
};

#endif
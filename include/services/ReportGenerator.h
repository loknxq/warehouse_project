// warehouse_project/include/services/ReportGenerator.h
#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>
#include <vector>
#include "../core/Product.h"
#include "../core/Stock.h"

class ReportGenerator {
public:
    static std::string generateStockReport(const std::vector<Stock>& stocks, 
                                            const std::string& date);
    static std::string generateMovementReport(const std::string& startDate,
                                               const std::string& endDate);
    static std::string generateTopProductsReport(const std::vector<std::pair<Product, int>>& sales);
    static std::string generateOrderListReport(const std::vector<std::pair<Product, int>>& toOrder);
    
    static std::string addFilter(const std::string& report, const std::string& category);
    static std::string addValueColumn(const std::string& report, 
                                       const std::vector<Stock>& stocks);
};

#endif
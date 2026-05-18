#include "../../include/services/ReportGenerator.h"
#include <sstream>

std::string ReportGenerator::generateStockReport(const std::vector<Stock>& stocks,
                                                   const std::string& date) {
    std::stringstream ss;
    ss << "=== STOCK REPORT FOR " << date << " ===\n";
    ss << "ID\tName\t\tQuantity\n";
    ss << "--------------------------------\n";
    
    for (const auto& stock : stocks) {
        if (stock.getProduct()) {
            ss << stock.getProduct()->getId() << "\t"
               << stock.getProduct()->getName() << "\t\t"
               << stock.getCurrentQuantity() << "\n";
        }
    }
    return ss.str();
}

std::string ReportGenerator::generateMovementReport(const std::string& startDate,
                                                      const std::string& endDate) {
    std::stringstream ss;
    ss << "=== MOVEMENT REPORT (" << startDate << " - " << endDate << ") ===\n";
    ss << "Movement report placeholder\n";
    return ss.str();
}

std::string ReportGenerator::generateTopProductsReport(const std::vector<std::pair<Product, int>>& sales) {
    std::stringstream ss;
    ss << "=== TOP 10 PRODUCTS ===\n";
    ss << "Name\t\tSales Count\n";
    ss << "------------------------\n";
    
    for (size_t i = 0; i < sales.size() && i < 10; ++i) {
        ss << sales[i].first.getName() << "\t\t" << sales[i].second << "\n";
    }
    return ss.str();
}

std::string ReportGenerator::generateOrderListReport(const std::vector<std::pair<Product, int>>& toOrder) {
    std::stringstream ss;
    ss << "=== PRODUCTS TO ORDER ===\n";
    ss << "Product\t\tRecommended Qty\n";
    ss << "---------------------------\n";
    
    for (const auto& item : toOrder) {
        ss << item.first.getName() << "\t\t" << item.second << "\n";
    }
    return ss.str();
}

std::string ReportGenerator::addFilter(const std::string& report, const std::string& category) {
    return "FILTERED(" + category + "):\n" + report;
}

std::string ReportGenerator::addValueColumn(const std::string& report,
                                              const std::vector<Stock>& stocks) {
    return report + "\n[Value column added]";
}
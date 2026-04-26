#include "services/ReportGenerator.h"
#include <iostream>
#include <sstream>

std::string StockReport::generate() {
    std::stringstream ss;
    ss << "=== ОТЧЁТ ПО ОСТАТКАМ ===" << std::endl;
    ss << "Товар А: 150 штук" << std::endl;
    ss << "Товар Б: 42 штуки" << std::endl;
    ss << "Товар В: 7 штук" << std::endl;
    ss << "Товар Г: 23 штуки" << std::endl;
    return ss.str();
}

std::string MovementReport::generate() {
    std::stringstream ss;
    ss << "=== ОТЧЁТ ПО ДВИЖЕНИЮ ТОВАРОВ ===" << std::endl;
    ss << "01.04.2026: Приход 100 шт. товара А" << std::endl;
    ss << "02.04.2026: Расход 30 шт. товара А" << std::endl;
    ss << "03.04.2026: Приход 50 шт. товара Б" << std::endl;
    return ss.str();
}

ReportDecorator::ReportDecorator(Report* report) {
    wrapped = report;
}

ReportDecorator::~ReportDecorator() {
    delete wrapped;
}

FilterDecorator::FilterDecorator(Report* report, std::string category) : ReportDecorator(report) {
    this->category = category;
}

std::string FilterDecorator::generate() {
    std::string base = wrapped->generate();
    std::stringstream ss;
    ss << base << std::endl;
    ss << "=== ФИЛЬТР ПО КАТЕГОРИИ: " << category << " ===" << std::endl;
    ss << "(отфильтрованные данные)" << std::endl;
    return ss.str();
}

ValueDecorator::ValueDecorator(Report* report) : ReportDecorator(report) {}

std::string ValueDecorator::generate() {
    std::string base = wrapped->generate();
    std::stringstream ss;
    ss << base << std::endl;
    ss << "=== ОБЩАЯ СТОИМОСТЬ ===" << std::endl;
    ss << "Общая стоимость всех товаров: 125 000 руб." << std::endl;
    return ss.str();
}
#include <iostream>
#include <string>
#include <vector>

#include "core/Product.h"
#include "core/Stock.h"
#include "core/Supplier.h"
#include "core/User.h"
#include "documents/IncomingOperation.h"
#include "documents/OutgoingOperation.h"
#include "services/Logger.h"
#include "services/OrderCalculator.h"
#include "services/ReportGenerator.h"
#include "strategies/AverageSalesStrategy.h"

// Пример класса-наблюдателя для создания заказов при достижении минимального порога
class ReorderNotifier : public Observer {
public:
    void update(int productId, int newQuantity) override {
        std::cout << "[ReorderNotifier] Товар " << productId 
                  << " достиг остатка " << newQuantity 
                  << ". Нужно создать заказ поставщику." << std::endl;
    }
};

void showMenu() {
    std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ ===" << std::endl;
    std::cout << "1. Оформить приход товара" << std::endl;
    std::cout << "2. Оформить расход товара" << std::endl;
    std::cout << "3. Показать остатки" << std::endl;
    std::cout << "4. Проверить товары к заказу" << std::endl;
    std::cout << "5. Сформировать отчёт" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

void demoFactoryMethod() {
    std::cout << "\n--- Демонстрация паттерна Фабричный метод ---" << std::endl;
    
    IncomingFactory incomingFactory;
    Document* doc1 = incomingFactory.createDocument();
    std::cout << "Создан документ типа: " << doc1->getType() << std::endl;
    delete doc1;
    
    OutgoingFactory outgoingFactory;
    Document* doc2 = outgoingFactory.createDocument();
    std::cout << "Создан документ типа: " << doc2->getType() << std::endl;
    delete doc2;
}

void demoObserver() {
    std::cout << "\n--- Демонстрация паттерна Наблюдатель ---" << std::endl;
    
    Stock stock(1, 12, 20);  // товар 1, остаток 12, минимальный порог 20
    ReorderNotifier notifier;
    stock.attach(&notifier);
    
    std::cout << "Текущий остаток товара 1: " << stock.getCurrentQuantity() << std::endl;
    std::cout << "Уменьшаем остаток на 5..." << std::endl;
    stock.decreaseQuantity(5);
    std::cout << "Остаток после уменьшения: " << stock.getCurrentQuantity() << std::endl;
}

void demoStrategy() {
    std::cout << "\n--- Демонстрация паттерна Стратегия ---" << std::endl;
    
    OrderCalculator calculator;
    AverageSalesStrategy strategy;
    
    calculator.setStrategy(&strategy);
    int recommendation = calculator.calculateRecommendation(1, 12, 20);
    std::cout << "Рекомендуемое количество для заказа: " << recommendation << std::endl;
}

void demoSingleton() {
    std::cout << "\n--- Демонстрация паттерна Одиночка ---" << std::endl;
    
    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();
    
    if (logger1 == logger2) {
        std::cout << "Оба указателя указывают на один и тот же объект Logger" << std::endl;
    }
    
    logger1->log("Система запущена");
    logger1->log("storekeeper", "create_incoming", "накладная №123");
}

void demoDecorator() {
    std::cout << "\n--- Демонстрация паттерна Декоратор ---" << std::endl;
    
    Report* baseReport = new StockReport();
    std::cout << "Базовый отчёт:" << std::endl;
    std::cout << baseReport->generate() << std::endl;
    
    Report* filteredReport = new FilterDecorator(baseReport, "электроника");
    std::cout << "Отчёт с фильтром:" << std::endl;
    std::cout << filteredReport->generate() << std::endl;
    
    Report* valuedReport = new ValueDecorator(filteredReport);
    std::cout << "Отчёт с фильтром и стоимостью:" << std::endl;
    std::cout << valuedReport->generate() << std::endl;
    
    delete valuedReport;
}

int main() {
    std::cout << "Система управления складом запущена" << std::endl;
    
    // Демонстрация всех паттернов
    demoFactoryMethod();
    demoObserver();
    demoStrategy();
    demoSingleton();
    demoDecorator();
    
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::cout << "Оформление прихода товара" << std::endl;
                IncomingOperation operation(1, "2026-04-26", "INV-001", 1);
                operation.addItem(1, 100, 50.0);
                operation.addItem(2, 50, 30.0);
                if (operation.validate()) {
                    operation.save();
                    Logger::getInstance()->log("storekeeper", "create_incoming", operation.getIncomingNumber());
                }
                break;
            }
            case 2: {
                std::cout << "Оформление расхода товара" << std::endl;
                OutgoingOperation operation(1, "2026-04-26", "ORD-001", "ООО Ромашка");
                operation.addItem(1, 30, 120.0);
                if (operation.validate()) {
                    operation.save();
                    Logger::getInstance()->log("storekeeper", "create_outgoing", operation.getCustomerOrderNumber());
                }
                break;
            }
            case 3: {
                std::cout << "Текущие остатки:" << std::endl;
                StockReport report;
                std::cout << report.generate();
                break;
            }
            case 4: {
                std::cout << "Проверка товаров к заказу" << std::endl;
                OrderCalculator calc;
                AverageSalesStrategy strat;
                calc.setStrategy(&strat);
                int rec = calc.calculateRecommendation(1, 12, 20);
                std::cout << "Рекомендуется заказать товар 1 в количестве: " << rec << std::endl;
                break;
            }
            case 5: {
                std::cout << "Формирование отчёта" << std::endl;
                MovementReport movementReport;
                std::cout << movementReport.generate();
                break;
            }
            case 0: {
                std::cout << "Выход из системы" << std::endl;
                Logger::getInstance()->log("Система завершила работу");
                break;
            }
            default: {
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
            }
        }
    } while (choice != 0);
    
    return 0;
}
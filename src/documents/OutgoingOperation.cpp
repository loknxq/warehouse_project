#include "documents/OutgoingOperation.h"
#include <iostream>

OutgoingItem::OutgoingItem() {
    productId = 0;
    quantity = 0;
    sellingPrice = 0.0;
}

OutgoingItem::OutgoingItem(int productId, int quantity, double sellingPrice) {
    this->productId = productId;
    this->quantity = quantity;
    this->sellingPrice = sellingPrice;
}

int OutgoingItem::getProductId() const { return productId; }
int OutgoingItem::getQuantity() const { return quantity; }
double OutgoingItem::getSellingPrice() const { return sellingPrice; }

OutgoingOperation::OutgoingOperation() {
    id = 0;
    date = "";
    customerOrderNumber = "";
    customerName = "";
}

OutgoingOperation::OutgoingOperation(int id, std::string date, std::string customerOrderNumber, std::string customerName) {
    this->id = id;
    this->date = date;
    this->customerOrderNumber = customerOrderNumber;
    this->customerName = customerName;
}

void OutgoingOperation::addItem(int productId, int quantity, double price) {
    items.push_back(OutgoingItem(productId, quantity, price));
}

bool OutgoingOperation::validate() {
    if (customerOrderNumber.empty()) {
        std::cout << "Ошибка: номер заказа клиента не может быть пустым" << std::endl;
        return false;
    }
    if (customerName.empty()) {
        std::cout << "Ошибка: имя клиента не может быть пустым" << std::endl;
        return false;
    }
    if (items.empty()) {
        std::cout << "Ошибка: операция не содержит товаров" << std::endl;
        return false;
    }
    for (const auto& item : items) {
        if (item.getQuantity() <= 0) {
            std::cout << "Ошибка: количество товара должно быть положительным" << std::endl;
            return false;
        }
        if (item.getSellingPrice() < 0) {
            std::cout << "Ошибка: цена не может быть отрицательной" << std::endl;
            return false;
        }
    }
    return true;
}

void OutgoingOperation::save() {
    std::cout << "Сохранение расходной операции по заказу " << customerOrderNumber << " в базу данных" << std::endl;
    for (const auto& item : items) {
        std::cout << "  Товар " << item.getProductId() << " количество " << item.getQuantity() << std::endl;
    }
}

std::string OutgoingOperation::getType() const {
    return "OutgoingOperation";
}

int OutgoingOperation::getId() const { return id; }
std::string OutgoingOperation::getDate() const { return date; }
std::string OutgoingOperation::getCustomerOrderNumber() const { return customerOrderNumber; }
std::string OutgoingOperation::getCustomerName() const { return customerName; }
const std::vector<OutgoingItem>& OutgoingOperation::getItems() const { return items; }

Document* OutgoingFactory::createDocument() {
    return new OutgoingOperation();
}
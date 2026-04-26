#include "documents/IncomingOperation.h"
#include <iostream>

IncomingItem::IncomingItem() {
    productId = 0;
    quantity = 0;
    purchasePrice = 0.0;
}

IncomingItem::IncomingItem(int productId, int quantity, double purchasePrice) {
    this->productId = productId;
    this->quantity = quantity;
    this->purchasePrice = purchasePrice;
}

int IncomingItem::getProductId() const { return productId; }
int IncomingItem::getQuantity() const { return quantity; }
double IncomingItem::getPurchasePrice() const { return purchasePrice; }

IncomingOperation::IncomingOperation() {
    id = 0;
    date = "";
    incomingNumber = "";
    supplierId = 0;
}

IncomingOperation::IncomingOperation(int id, std::string date, std::string incomingNumber, int supplierId) {
    this->id = id;
    this->date = date;
    this->incomingNumber = incomingNumber;
    this->supplierId = supplierId;
}

void IncomingOperation::addItem(int productId, int quantity, double price) {
    items.push_back(IncomingItem(productId, quantity, price));
}

bool IncomingOperation::validate() {
    if (incomingNumber.empty()) {
        std::cout << "Ошибка: номер накладной не может быть пустым" << std::endl;
        return false;
    }
    if (supplierId <= 0) {
        std::cout << "Ошибка: поставщик не выбран" << std::endl;
        return false;
    }
    if (items.empty()) {
        std::cout << "Ошибка: накладная не содержит товаров" << std::endl;
        return false;
    }
    for (const auto& item : items) {
        if (item.getQuantity() <= 0) {
            std::cout << "Ошибка: количество товара должно быть положительным" << std::endl;
            return false;
        }
        if (item.getPurchasePrice() < 0) {
            std::cout << "Ошибка: цена не может быть отрицательной" << std::endl;
            return false;
        }
    }
    return true;
}

void IncomingOperation::save() {
    std::cout << "Сохранение приходной операции " << incomingNumber << " в базу данных" << std::endl;
    for (const auto& item : items) {
        std::cout << "  Товар " << item.getProductId() << " количество " << item.getQuantity() << std::endl;
    }
}

std::string IncomingOperation::getType() const {
    return "IncomingOperation";
}

int IncomingOperation::getId() const { return id; }
std::string IncomingOperation::getDate() const { return date; }
std::string IncomingOperation::getIncomingNumber() const { return incomingNumber; }
int IncomingOperation::getSupplierId() const { return supplierId; }
const std::vector<IncomingItem>& IncomingOperation::getItems() const { return items; }

Document* IncomingFactory::createDocument() {
    return new IncomingOperation();
}
#include "../../include/documents/IncomingOperation.h"

IncomingItem::IncomingItem(std::shared_ptr<Product> p, int q, double price)
    : product(p), quantity(q), actualPrice(price) {}

IncomingOperation::IncomingOperation() : Document(), supplier(nullptr), invoiceNumber("") {}

IncomingOperation::IncomingOperation(int id, const std::string& docNumber,
                                      std::shared_ptr<Supplier> supplier,
                                      const std::string& invoiceNumber)
    : Document(id, docNumber), supplier(supplier), invoiceNumber(invoiceNumber) {}

void IncomingOperation::addItem(std::shared_ptr<Product> product, int quantity, double price) {
    items.emplace_back(product, quantity, price);
}

void IncomingOperation::removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items.erase(items.begin() + index);
    }
}

void IncomingOperation::clearItems() { items.clear(); }

std::vector<IncomingItem> IncomingOperation::getItems() const { return items; }
std::shared_ptr<Supplier> IncomingOperation::getSupplier() const { return supplier; }
std::string IncomingOperation::getInvoiceNumber() const { return invoiceNumber; }

double IncomingOperation::getTotalValue() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.quantity * item.actualPrice;
    }
    return total;
}

int IncomingOperation::getTotalQuantity() const {
    int total = 0;
    for (const auto& item : items) {
        total += item.quantity;
    }
    return total;
}

bool IncomingOperation::saveToDatabase() const {
    // Имитация сохранения в БД
    return validate();
}

bool IncomingOperation::validate() const {
    if (id <= 0) return false;
    if (documentNumber.empty()) return false;
    if (!supplier) return false;
    if (invoiceNumber.empty()) return false;
    if (items.empty()) return false;
    
    for (const auto& item : items) {
        if (!item.product || item.quantity <= 0 || item.actualPrice < 0) {
            return false;
        }
    }
    return true;
}

std::string IncomingOperation::getType() const { return "INCOMING"; }
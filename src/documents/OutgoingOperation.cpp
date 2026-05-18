#include "../../include/documents/OutgoingOperation.h"

OutgoingItem::OutgoingItem(std::shared_ptr<Product> p, int q, double price)
    : product(p), quantity(q), sellingPrice(price) {}

OutgoingOperation::OutgoingOperation() : Document(), customerName(""), customerOrderNumber("") {}

OutgoingOperation::OutgoingOperation(int id, const std::string& docNumber,
                                      const std::string& customerName,
                                      const std::string& customerOrderNumber)
    : Document(id, docNumber), customerName(customerName), 
      customerOrderNumber(customerOrderNumber) {}

void OutgoingOperation::addItem(std::shared_ptr<Product> product, int quantity, double price) {
    items.emplace_back(product, quantity, price);
}

void OutgoingOperation::removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items.erase(items.begin() + index);
    }
}

void OutgoingOperation::clearItems() { items.clear(); }

std::vector<OutgoingItem> OutgoingOperation::getItems() const { return items; }
std::string OutgoingOperation::getCustomerName() const { return customerName; }
std::string OutgoingOperation::getCustomerOrderNumber() const { return customerOrderNumber; }

double OutgoingOperation::getTotalValue() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.quantity * item.sellingPrice;
    }
    return total;
}

int OutgoingOperation::getTotalQuantity() const {
    int total = 0;
    for (const auto& item : items) {
        total += item.quantity;
    }
    return total;
}

bool OutgoingOperation::saveToDatabase() const {
    return validate();
}

bool OutgoingOperation::validate() const {
    if (id <= 0) return false;
    if (documentNumber.empty()) return false;
    if (customerName.empty()) return false;
    if (customerOrderNumber.empty()) return false;
    if (items.empty()) return false;
    
    for (const auto& item : items) {
        if (!item.product || item.quantity <= 0 || item.sellingPrice < 0) {
            return false;
        }
    }
    return true;
}

std::string OutgoingOperation::getType() const { return "OUTGOING"; }
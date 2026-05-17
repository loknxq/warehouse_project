// warehouse_project/include/documents/OutgoingOperation.h
#ifndef OUTGOING_OPERATION_H
#define OUTGOING_OPERATION_H

#include "Document.h"
#include "../core/Product.h"
#include <vector>
#include <memory>
#include <string>

struct OutgoingItem {
    std::shared_ptr<Product> product;
    int quantity;
    double sellingPrice;
    
    OutgoingItem(std::shared_ptr<Product> p, int q, double price);
};

class OutgoingOperation : public Document {
private:
    std::string customerName;
    std::string customerOrderNumber;
    std::vector<OutgoingItem> items;

public:
    OutgoingOperation();
    OutgoingOperation(int id, const std::string& docNumber,
                      const std::string& customerName,
                      const std::string& customerOrderNumber);
    
    void addItem(std::shared_ptr<Product> product, int quantity, double price);
    void removeItem(int index);
    void clearItems();
    
    std::vector<OutgoingItem> getItems() const;
    std::string getCustomerName() const;
    std::string getCustomerOrderNumber() const;
    
    double getTotalValue() const;
    int getTotalQuantity() const;
    
    bool saveToDatabase() const override;
    bool validate() const override;
    std::string getType() const override;
};

#endif
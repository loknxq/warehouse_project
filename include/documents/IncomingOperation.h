#ifndef INCOMING_OPERATION_H
#define INCOMING_OPERATION_H

#include "Document.h"
#include "../core/Product.h"
#include "../core/Supplier.h"
#include <vector>
#include <memory>

struct IncomingItem {
    std::shared_ptr<Product> product;
    int quantity;
    double actualPrice;
    
    IncomingItem(std::shared_ptr<Product> p, int q, double price);
};

class IncomingOperation : public Document {
private:
    std::shared_ptr<Supplier> supplier;
    std::vector<IncomingItem> items;
    std::string invoiceNumber;

public:
    IncomingOperation();
    IncomingOperation(int id, const std::string& docNumber, 
                      std::shared_ptr<Supplier> supplier, 
                      const std::string& invoiceNumber);
    
    void addItem(std::shared_ptr<Product> product, int quantity, double price);
    void removeItem(int index);
    void clearItems();
    
    std::vector<IncomingItem> getItems() const;
    std::shared_ptr<Supplier> getSupplier() const;
    std::string getInvoiceNumber() const;
    
    double getTotalValue() const;
    int getTotalQuantity() const;
    
    bool saveToDatabase() const override;
    bool validate() const override;
    std::string getType() const override;
};

#endif
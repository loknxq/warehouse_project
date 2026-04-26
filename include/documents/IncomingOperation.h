#ifndef INCOMING_OPERATION_H
#define INCOMING_OPERATION_H

#include "documents/Document.h"
#include "core/Supplier.h"
#include <string>
#include <vector>

class IncomingItem {
private:
    int productId;
    int quantity;
    double purchasePrice;

public:
    IncomingItem();
    IncomingItem(int productId, int quantity, double purchasePrice);

    int getProductId() const;
    int getQuantity() const;
    double getPurchasePrice() const;
};

class IncomingOperation : public Document {
private:
    int id;
    std::string date;
    std::string incomingNumber;
    int supplierId;
    std::vector<IncomingItem> items;

public:
    IncomingOperation();
    IncomingOperation(int id, std::string date, std::string incomingNumber, int supplierId);

    void addItem(int productId, int quantity, double price);
    void save() override;
    bool validate() override;
    std::string getType() const override;

    int getId() const;
    std::string getDate() const;
    std::string getIncomingNumber() const;
    int getSupplierId() const;
    const std::vector<IncomingItem>& getItems() const;
};

class IncomingFactory : public DocumentFactory {
public:
    Document* createDocument() override;
};

#endif
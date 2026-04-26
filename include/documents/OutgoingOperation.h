#ifndef OUTGOING_OPERATION_H
#define OUTGOING_OPERATION_H

#include "documents/Document.h"
#include <string>
#include <vector>

class OutgoingItem {
private:
    int productId;
    int quantity;
    double sellingPrice;

public:
    OutgoingItem();
    OutgoingItem(int productId, int quantity, double sellingPrice);

    int getProductId() const;
    int getQuantity() const;
    double getSellingPrice() const;
};

class OutgoingOperation : public Document {
private:
    int id;
    std::string date;
    std::string customerOrderNumber;
    std::string customerName;
    std::vector<OutgoingItem> items;

public:
    OutgoingOperation();
    OutgoingOperation(int id, std::string date, std::string customerOrderNumber, std::string customerName);

    void addItem(int productId, int quantity, double price);
    void save() override;
    bool validate() override;
    std::string getType() const override;

    int getId() const;
    std::string getDate() const;
    std::string getCustomerOrderNumber() const;
    std::string getCustomerName() const;
    const std::vector<OutgoingItem>& getItems() const;
};

class OutgoingFactory : public DocumentFactory {
public:
    Document* createDocument() override;
};

#endif
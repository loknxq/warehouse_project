#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string article;
    std::string category;
    std::string unit;
    double purchasePrice;
    double sellingPrice;
    int minStock;

public:
    Product();
    Product(int id, std::string name, std::string article, std::string category,
            std::string unit, double purchasePrice, double sellingPrice, int minStock);

    int getId() const;
    std::string getName() const;
    std::string getArticle() const;
    std::string getCategory() const;
    std::string getUnit() const;
    double getPurchasePrice() const;
    double getSellingPrice() const;
    int getMinStock() const;

    void setName(std::string name);
    void setCategory(std::string category);
    void setPurchasePrice(double price);
    void setSellingPrice(double price);
    void setMinStock(int minStock);
};

#endif
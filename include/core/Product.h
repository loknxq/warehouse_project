// warehouse_project/include/core/Product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <memory>

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
    Product(int id, const std::string& name, const std::string& article,
            const std::string& category, const std::string& unit,
            double purchasePrice, double sellingPrice, int minStock);
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getArticle() const;
    std::string getCategory() const;
    std::string getUnit() const;
    double getPurchasePrice() const;
    double getSellingPrice() const;
    int getMinStock() const;
    
    // Setters
    void setId(int newId);
    void setName(const std::string& newName);
    void setArticle(const std::string& newArticle);
    void setCategory(const std::string& newCategory);
    void setUnit(const std::string& newUnit);
    void setPurchasePrice(double newPrice);
    void setSellingPrice(double newPrice);
    void setMinStock(int newMinStock);
    
    // Methods
    bool isValid() const;
    double calculateProfitMargin() const;
    
    bool operator==(const Product& other) const;
};

#endif
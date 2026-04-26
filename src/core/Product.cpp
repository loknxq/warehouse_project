#include "core/Product.h"

Product::Product() {
    id = 0;
    name = "";
    article = "";
    category = "";
    unit = "";
    purchasePrice = 0.0;
    sellingPrice = 0.0;
    minStock = 0;
}

Product::Product(int id, std::string name, std::string article, std::string category,
                 std::string unit, double purchasePrice, double sellingPrice, int minStock) {
    this->id = id;
    this->name = name;
    this->article = article;
    this->category = category;
    this->unit = unit;
    this->purchasePrice = purchasePrice;
    this->sellingPrice = sellingPrice;
    this->minStock = minStock;
}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getArticle() const { return article; }
std::string Product::getCategory() const { return category; }
std::string Product::getUnit() const { return unit; }
double Product::getPurchasePrice() const { return purchasePrice; }
double Product::getSellingPrice() const { return sellingPrice; }
int Product::getMinStock() const { return minStock; }

void Product::setName(std::string name) { this->name = name; }
void Product::setCategory(std::string category) { this->category = category; }
void Product::setPurchasePrice(double price) { this->purchasePrice = price; }
void Product::setSellingPrice(double price) { this->sellingPrice = price; }
void Product::setMinStock(int minStock) { this->minStock = minStock; }
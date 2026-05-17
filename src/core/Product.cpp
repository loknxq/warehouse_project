// warehouse_project/src/core/Product.cpp
#include "../../include/core/Product.h"

Product::Product() : id(0), name(""), article(""), category(""), 
                     unit(""), purchasePrice(0.0), sellingPrice(0.0), minStock(0) {}

Product::Product(int id, const std::string& name, const std::string& article,
                 const std::string& category, const std::string& unit,
                 double purchasePrice, double sellingPrice, int minStock)
    : id(id), name(name), article(article), category(category), unit(unit),
      purchasePrice(purchasePrice), sellingPrice(sellingPrice), minStock(minStock) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getArticle() const { return article; }
std::string Product::getCategory() const { return category; }
std::string Product::getUnit() const { return unit; }
double Product::getPurchasePrice() const { return purchasePrice; }
double Product::getSellingPrice() const { return sellingPrice; }
int Product::getMinStock() const { return minStock; }

void Product::setId(int newId) { id = newId; }
void Product::setName(const std::string& newName) { name = newName; }
void Product::setArticle(const std::string& newArticle) { article = newArticle; }
void Product::setCategory(const std::string& newCategory) { category = newCategory; }
void Product::setUnit(const std::string& newUnit) { unit = newUnit; }
void Product::setPurchasePrice(double newPrice) { purchasePrice = newPrice; }
void Product::setSellingPrice(double newPrice) { sellingPrice = newPrice; }
void Product::setMinStock(int newMinStock) { minStock = newMinStock; }

bool Product::isValid() const {
    return id > 0 && !name.empty() && !article.empty() && 
           purchasePrice >= 0 && sellingPrice >= 0 && minStock >= 0;
}

double Product::calculateProfitMargin() const {
    if (purchasePrice == 0) return 0;
    return ((sellingPrice - purchasePrice) / purchasePrice) * 100;
}

bool Product::operator==(const Product& other) const {
    return id == other.id && name == other.name && article == other.article;
}
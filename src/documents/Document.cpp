// warehouse_project/src/documents/Document.cpp
#include "../../include/documents/Document.h"
#include <ctime>

Document::Document() : id(0), date(std::time(nullptr)), documentNumber("") {}

Document::Document(int id, const std::string& documentNumber) 
    : id(id), date(std::time(nullptr)), documentNumber(documentNumber) {}

int Document::getId() const { return id; }
std::time_t Document::getDate() const { return date; }
std::string Document::getDocumentNumber() const { return documentNumber; }

void Document::setDocumentNumber(const std::string& number) { documentNumber = number; }
void Document::setDate(std::time_t newDate) { date = newDate; }
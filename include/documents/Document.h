#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <ctime>

class Document {
protected:
    int id;
    std::time_t date;
    std::string documentNumber;

public:
    Document();
    Document(int id, const std::string& documentNumber);
    virtual ~Document() = default;
    
    int getId() const;
    std::time_t getDate() const;
    std::string getDocumentNumber() const;
    
    virtual bool saveToDatabase() const = 0;
    virtual bool validate() const = 0;
    virtual std::string getType() const = 0;
    
    void setDocumentNumber(const std::string& number);
    void setDate(std::time_t newDate);
};

#endif
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

class Document {
public:
    virtual ~Document() {}
    virtual void save() = 0;
    virtual bool validate() = 0;
    virtual std::string getType() const = 0;
};

class DocumentFactory {
public:
    virtual ~DocumentFactory() {}
    virtual Document* createDocument() = 0;
};

#endif
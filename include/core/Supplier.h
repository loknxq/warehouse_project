#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <memory>

class Supplier {
private:
    int id;
    std::string name;
    std::string contactPerson;
    std::string phone;
    std::string email;

public:
    Supplier();
    Supplier(int id, const std::string& name, const std::string& contactPerson,
             const std::string& phone, const std::string& email);
    
    int getId() const;
    std::string getName() const;
    std::string getContactPerson() const;
    std::string getPhone() const;
    std::string getEmail() const;
    
    void setId(int newId);
    void setName(const std::string& newName);
    void setContactPerson(const std::string& newContact);
    void setPhone(const std::string& newPhone);
    void setEmail(const std::string& newEmail);
    
    bool isValid() const;
    
    bool operator==(const Supplier& other) const;
};

#endif
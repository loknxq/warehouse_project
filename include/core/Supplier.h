#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>

class Supplier {
private:
    int id;
    std::string name;
    std::string contactPerson;
    std::string phone;
    std::string email;

public:
    Supplier();
    Supplier(int id, std::string name, std::string contactPerson,
             std::string phone, std::string email);

    int getId() const;
    std::string getName() const;
    std::string getContactPerson() const;
    std::string getPhone() const;
    std::string getEmail() const;

    void setName(std::string name);
    void setContactPerson(std::string contactPerson);
    void setPhone(std::string phone);
    void setEmail(std::string email);
};

#endif
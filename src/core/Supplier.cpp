#include "core/Supplier.h"

Supplier::Supplier() {
    id = 0;
    name = "";
    contactPerson = "";
    phone = "";
    email = "";
}

Supplier::Supplier(int id, std::string name, std::string contactPerson,
                   std::string phone, std::string email) {
    this->id = id;
    this->name = name;
    this->contactPerson = contactPerson;
    this->phone = phone;
    this->email = email;
}

int Supplier::getId() const { return id; }
std::string Supplier::getName() const { return name; }
std::string Supplier::getContactPerson() const { return contactPerson; }
std::string Supplier::getPhone() const { return phone; }
std::string Supplier::getEmail() const { return email; }

void Supplier::setName(std::string name) { this->name = name; }
void Supplier::setContactPerson(std::string contactPerson) { this->contactPerson = contactPerson; }
void Supplier::setPhone(std::string phone) { this->phone = phone; }
void Supplier::setEmail(std::string email) { this->email = email; }
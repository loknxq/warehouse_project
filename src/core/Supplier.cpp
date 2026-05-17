// warehouse_project/src/core/Supplier.cpp
#include "../../include/core/Supplier.h"

Supplier::Supplier() : id(0), name(""), contactPerson(""), phone(""), email("") {}

Supplier::Supplier(int id, const std::string& name, const std::string& contactPerson,
                   const std::string& phone, const std::string& email)
    : id(id), name(name), contactPerson(contactPerson), phone(phone), email(email) {}

int Supplier::getId() const { return id; }
std::string Supplier::getName() const { return name; }
std::string Supplier::getContactPerson() const { return contactPerson; }
std::string Supplier::getPhone() const { return phone; }
std::string Supplier::getEmail() const { return email; }

void Supplier::setId(int newId) { id = newId; }
void Supplier::setName(const std::string& newName) { name = newName; }
void Supplier::setContactPerson(const std::string& newContact) { contactPerson = newContact; }
void Supplier::setPhone(const std::string& newPhone) { phone = newPhone; }
void Supplier::setEmail(const std::string& newEmail) { email = newEmail; }

bool Supplier::isValid() const {
    return id > 0 && !name.empty() && !contactPerson.empty() && 
           !phone.empty() && !email.empty();
}

bool Supplier::operator==(const Supplier& other) const {
    return id == other.id && name == other.name;
}
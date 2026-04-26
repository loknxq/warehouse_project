#include "core/User.h"
#include <string>

User::User() {
    id = 0;
    login = "";
    passwordHash = "";
    role = Role::STOREKEEPER;
}

User::User(int id, std::string login, std::string passwordHash, Role role) {
    this->id = id;
    this->login = login;
    this->passwordHash = passwordHash;
    this->role = role;
}

int User::getId() const { return id; }
std::string User::getLogin() const { return login; }
std::string User::getPasswordHash() const { return passwordHash; }
Role User::getRole() const { return role; }

void User::setPasswordHash(std::string newHash) {
    passwordHash = newHash;
}

bool User::authenticate(std::string password) const {
    // В реальном проекте здесь было бы хэширование пароля и сравнение
    // Для примера просто сравниваем с пустой строкой
    return password == passwordHash;
}
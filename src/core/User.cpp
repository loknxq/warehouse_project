#include "../../include/core/User.h"
#include <functional>
#include <string>

std::string User::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

User::User() : id(0), login(""), passwordHash(""), role(UserRole::STOREKEEPER) {}

User::User(int id, const std::string& login, const std::string& password, UserRole role)
    : id(id), login(login), passwordHash(hashPassword(password)), role(role) {}

int User::getId() const { return id; }
std::string User::getLogin() const { return login; }
UserRole User::getRole() const { return role; }

bool User::authenticate(const std::string& password) const {
    return passwordHash == hashPassword(password);
}

bool User::hasPermission(UserRole requiredRole) const {
    // Пользователь имеет доступ, если его роль >= требуемой роли
    return static_cast<int>(role) >= static_cast<int>(requiredRole);
}

void User::logout() {
    // Логика выхода из системы
}

std::string User::getRoleString() const {
    switch(role) {
        case UserRole::STOREKEEPER: return "STOREKEEPER";
        case UserRole::MANAGER: return "MANAGER";
        case UserRole::WAREHOUSE_HEAD: return "WAREHOUSE_HEAD";
        case UserRole::ADMIN: return "ADMIN";
        default: return "UNKNOWN";
    }
}

bool User::operator==(const User& other) const {
    return id == other.id && login == other.login && role == other.role;
}
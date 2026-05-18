#ifndef USER_H
#define USER_H

#include <string>
#include <functional>

enum class UserRole {
    STOREKEEPER = 0,
    MANAGER = 1,
    WAREHOUSE_HEAD = 2,
    ADMIN = 3
};

class User {
private:
    int id;
    std::string login;
    std::string passwordHash;
    UserRole role;
    
    static std::string hashPassword(const std::string& password);

public:
    User();
    User(int id, const std::string& login, const std::string& password, UserRole role);
    
    int getId() const;
    std::string getLogin() const;
    UserRole getRole() const;
    
    bool authenticate(const std::string& password) const;
    bool hasPermission(UserRole requiredRole) const;
    void logout();
    
    std::string getRoleString() const;
    
    bool operator==(const User& other) const;
};

#endif
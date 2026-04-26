#ifndef USER_H
#define USER_H

#include <string>

enum class Role {
    STOREKEEPER,
    MANAGER,
    WAREHOUSE_CHIEF,
    ADMIN
};

class User {
private:
    int id;
    std::string login;
    std::string passwordHash;
    Role role;

public:
    User();
    User(int id, std::string login, std::string passwordHash, Role role);

    int getId() const;
    std::string getLogin() const;
    std::string getPasswordHash() const;
    Role getRole() const;

    void setPasswordHash(std::string newHash);
    bool authenticate(std::string password) const;
};

#endif
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;

public:
    User(std::string user, std::string pass)
        : username(user), password(pass) {}

    std::string getUsername() const {
        return username;
    }

    bool authenticate(std::string user, std::string pass) const {
        return (username == user && password == pass);
    }
};

#endif // USER_H

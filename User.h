#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string username;
    string password;

public:
    User(string user, string pass) {
        username = user;
        password = pass;
    }

    string getUsername() const {
        return username;
    }

    bool authenticate(string user, string pass) const {
        return (username == user && password == pass);
    }
};

#endif // USER_H

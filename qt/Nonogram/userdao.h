#ifndef USERDAO_H
#define USERDAO_H

#include <vector>
#include "User.h"

class UserDAO {
public:
    virtual ~UserDAO() = default;

    virtual void insert(const User& user) = 0;
    virtual User getUserById(int userId) = 0;
    virtual void updateUser(const User& user) = 0;
    virtual void deleteUser(int userId) = 0;
    virtual std::vector<User> getAllUsers() = 0;
};

#endif // USERDAO_H

#ifndef USERDAO_H
#define USERDAO_H

#include <vector>
#include "User.h"

class UserDAO {
public:
    virtual ~UserDAO() = default;
    virtual std::vector<User> getAllUsers() const = 0;
    virtual void insert(const User& user) = 0;
    virtual void deleteUser(int userId) = 0;
    virtual User getUserById(int userId) const = 0;
    virtual void updateUser(const User& user) = 0;
};

#endif // USERDAO_H

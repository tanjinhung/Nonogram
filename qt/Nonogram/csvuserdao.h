#ifndef CSVUSERDAO_H
#define CSVUSERDAO_H

#include <QString>
#include <vector>
#include "User.h"

class CSVUserDAO {
public:
    CSVUserDAO(const QString &filename);
    std::vector<User> getAllUsers() const;
    void insert(const User &user);
    void deleteUser(int userId);
    int getNextUserId() const;

private:
    QString filename;
};

#endif // CSVUSERDAO_H

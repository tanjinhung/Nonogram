#ifndef CSVUSERDAO_H
#define CSVUSERDAO_H

#include "user.h"
#include "userdao.h"
#include <QString>
#include <vector>

class CSVUserDAO : public UserDAO {
public:
    CSVUserDAO(const QString &filename);
    std::vector<User> getAllUsers() const override;
    void insert(const User &user) override;
    void deleteUser(int userId) override;
    User getUserById(int userId) const override;
    void updateUser(const User &updatedUser) override;
    int getNextUserId() const;

private:
    QString filename;
};

#endif // CSVUSERDAO_H

#include "CSVUserDAO.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CSVUserDAO::CSVUserDAO(const QString &filename) : filename(filename) {}

std::vector<User> CSVUserDAO::getAllUsers() const {  // Ensure this matches the declaration
    std::vector<User> users;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filename;
        return users;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 6) {
            User user(fields[0].toInt(),
                      fields[1],
                      fields[2].toInt(),
                      fields[3].toInt(),
                      static_cast<qint64>(fields[4].toLongLong()),
                      static_cast<qint64>(fields[5].toLongLong()));
            users.push_back(user);
        }
    }

    file.close();
    return users;
}

void CSVUserDAO::insert(const User &user) {
    QFile file(filename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    out << user.getUserId() << ","
        << user.getName() << ","
        << user.getImageId() << ","
        << user.getLevelCompleted() << ","
        << static_cast<qint64>(user.getFastestCompleted()) << ","
        << static_cast<qint64>(user.getTotalTimePlayed()) << "\n";

    qDebug() << "Inserted user:" << user.getUserId() << user.getName();

    file.close();
}

void CSVUserDAO::deleteUser(int userId) {
    std::vector<User> users = getAllUsers();
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    for (const User &user : users) {
        if (user.getUserId() != userId) {
            out << user.getUserId() << ","
                << user.getName() << ","
                << user.getImageId() << ","
                << user.getLevelCompleted() << ","
                << static_cast<qint64>(user.getFastestCompleted()) << ","
                << static_cast<qint64>(user.getTotalTimePlayed()) << "\n";
        }
    }

    file.close();
}

int CSVUserDAO::getNextUserId() const
{
    int maxId = 0;
    std::vector<User> users = getAllUsers();
    for (const User &user : users) {
        maxId = std::max(maxId, user.getUserId());
    }
    return maxId + 1;
}

User CSVUserDAO::getUserById(int userId) const {
    std::vector<User> users = getAllUsers();
    for (const User &user : users) {
        if (user.getUserId() == userId) {
            return user;
        }
    }
    return User(-1, "Unnamed", -1, 0, 0, 0); // Return a default user if not found
}

void CSVUserDAO::updateUser(const User &updatedUser) {
    std::vector<User> users = getAllUsers();
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    for (const User &user : users) {
        if (user.getUserId() == updatedUser.getUserId()) {
            out << updatedUser.getUserId() << ","
                << updatedUser.getName() << ","
                << updatedUser.getImageId() << ","
                << updatedUser.getLevelCompleted() << ","
                << static_cast<qint64>(updatedUser.getFastestCompleted()) << ","
                << static_cast<qint64>(updatedUser.getTotalTimePlayed()) << "\n";
        } else {
            out << user.getUserId() << ","
                << user.getName() << ","
                << user.getImageId() << ","
                << user.getLevelCompleted() << ","
                << static_cast<qint64>(user.getFastestCompleted()) << ","
                << static_cast<qint64>(user.getTotalTimePlayed()) << "\n";
        }
    }

    file.close();
}

#include "ProfileController.h"

ProfileController::ProfileController(QObject *parent)
    : QObject(parent) {}

void ProfileController::registerUser(const QString &name, int imageNumber) {
    if (name.isEmpty()) {
        emit registrationFailed(QString("Name cannot be blank"));
        return;
    }

    CSVUserDAO userDAO(QString("users.csv"));
    int newUserId = userDAO.getNextUserId();
    User newUser(newUserId, name, imageNumber, 0, 0, 0); // Adjust parameters as needed
    userDAO.insert(newUser);
    emit registrationSucceeded();
}

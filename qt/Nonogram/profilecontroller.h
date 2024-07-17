#ifndef PROFILECONTROLLER_H
#define PROFILECONTROLLER_H

#include "user.h"
#include <QObject>

class ProfileController : public QObject {
    Q_OBJECT
public:
    explicit ProfileController(QObject *parent = nullptr);

signals:
    void registrationFailed(const QString &msg);
    void registrationSucceeded();
    void returnCurrentUser(User user);

public slots:
    void registerUser(const QString &name, int imageNumber);
    void updateTotalTimePlayed(int currentUserId, int timeElapsed);
    void confirmUserDeletion(int userId);
    void getCurrentUser(int userId);
};

#endif // PROFILECONTROLLER_H

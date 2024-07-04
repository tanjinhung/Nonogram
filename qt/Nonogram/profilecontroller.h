#ifndef PROFILECONTROLLER_H
#define PROFILECONTROLLER_H

#include <QObject>
#include "CSVUserDAO.h"

class ProfileController : public QObject {
    Q_OBJECT
public:
    explicit ProfileController(QObject *parent = nullptr);

signals:
    void registrationFailed(const QString &msg);
    void registrationSucceeded();

public slots:
    void registerUser(const QString &name, int imageNumber);
};

#endif // PROFILECONTROLLER_H

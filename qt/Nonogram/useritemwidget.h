#ifndef USERITEMWIDGET_H
#define USERITEMWIDGET_H

#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include "User.h"

class UserItemWidget : public QGraphicsView {
    Q_OBJECT

public:
    UserItemWidget(const User &user, QWidget *parent = nullptr);

signals:
    void selectUser(int userId);
    void deleteUser(int userId);

private slots:
    void onSelectButtonClicked();
    void onDeleteButtonClicked();

private:
    int userId;
    QGraphicsScene *scene;
    QLabel *imageLabel;
    QPushButton *selectButton;
    QPushButton *deleteButton;
};

#endif // USERITEMWIDGET_H

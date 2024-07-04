#include "UserItemWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

UserItemWidget::UserItemWidget(const User &user, QWidget *parent)
    : QWidget(parent), userId(user.getUserId()) {

    nameLabel = new QLabel(QString(user.getName()));
    imageIdLabel = new QLabel(QString::number(user.getImageId()));
    levelCompletedLabel = new QLabel(QString::number(user.getLevelCompleted()));
    fastestCompletedLabel = new QLabel(QString::number(user.getFastestCompleted()));
    totalTimePlayedLabel = new QLabel(QString::number(user.getTotalTimePlayed()));

    selectButton = new QPushButton("Select");
    deleteButton = new QPushButton("Delete");

    connect(selectButton, &QPushButton::clicked, this, &UserItemWidget::onSelectButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &UserItemWidget::onDeleteButtonClicked);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(selectButton);
    buttonLayout->addWidget(deleteButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(imageIdLabel);
    mainLayout->addWidget(levelCompletedLabel);
    mainLayout->addWidget(fastestCompletedLabel);
    mainLayout->addWidget(totalTimePlayedLabel);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void UserItemWidget::onSelectButtonClicked() {
    emit selectUser(userId);
}

void UserItemWidget::onDeleteButtonClicked() {
    emit deleteUser(userId);
}

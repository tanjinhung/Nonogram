#include "UserItemWidget.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QTime>

UserItemWidget::UserItemWidget(const User &user, QWidget *parent)
    : QGraphicsView(parent), userId(user.getUserId()), scene(new QGraphicsScene(this)) {

    setScene(scene);

    imageLabel = new QLabel();
    QPixmap pixmap(QString(":/image/%1.png").arg(user.getImageId()));
    imageLabel->setPixmap(pixmap.scaled(300, 420, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsProxyWidget *imageLabelProxy = scene->addWidget(imageLabel);
    imageLabelProxy->setPos(0, 0);

    QGraphicsTextItem *nameText = new QGraphicsTextItem(user.getName());
    QFont nameFont("Arial", 16);
    nameText->setFont(nameFont);
    nameText->setPos(150 - nameText->boundingRect().width()/2, 450);
    scene->addItem(nameText);

    QGraphicsTextItem *levelCompletedText = new QGraphicsTextItem(
        QString("Level Completed: %1").arg(user.getLevelCompleted(), 3, 10, QChar('0'))
    );
    levelCompletedText->setFont(nameFont);
    levelCompletedText->setPos(0, 550);
    scene->addItem(levelCompletedText);

    QGraphicsTextItem *fastestCompletedText = new QGraphicsTextItem(
        QString("Fastest Completed: %1").arg(user.getFastestCompletedTime().toString("mm:ss.zzz"))
    );
    fastestCompletedText->setFont(nameFont);
    fastestCompletedText->setPos(0, 600);
    scene->addItem(fastestCompletedText);

    QGraphicsTextItem *totalTimePlayedText = new QGraphicsTextItem(
        QString("Total Time Played: %1").arg(formatElapsedTime(user.getTotalTimePlayed()))
    );
    totalTimePlayedText->setFont(nameFont);
    totalTimePlayedText->setPos(0, 650);
    scene->addItem(totalTimePlayedText);

    selectButton = new QPushButton("Select");
    selectButton->setGeometry(0, 0, 150, 36);
    connect(selectButton, &QPushButton::clicked, this, &UserItemWidget::onSelectButtonClicked);
    QGraphicsProxyWidget *selectButtonProxy = scene->addWidget(selectButton);
    selectButtonProxy->setPos(0, 720);

    deleteButton = new QPushButton("Delete");
    deleteButton->setGeometry(0, 0, 150, 36);
    connect(deleteButton, &QPushButton::clicked, this, &UserItemWidget::onDeleteButtonClicked);
    QGraphicsProxyWidget *deleteButtonProxy = scene->addWidget(deleteButton);
    deleteButtonProxy->setPos(150, 720);
}

void UserItemWidget::onSelectButtonClicked() {
    emit selectUser(userId);
}

void UserItemWidget::onDeleteButtonClicked() {
    emit deleteUser(userId);
}

QString UserItemWidget::formatElapsedTime(qint64 elapsedTimeInMillis) const {
    int totalSeconds = elapsedTimeInMillis / 1000;

    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    return QString("%1:%2:%3")
        .arg(hours, 4, 10)
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}

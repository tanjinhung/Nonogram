#include "frame.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>

Frame::Frame(QWidget *parent)
{
    // constructor
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1600, 900);

    // scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1600, 900);
    setScene(scene);
}

void Frame::showMainMenu()
{
    // display title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Nonogram"));
    QFont titleFont("Courier New", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 300;
    titleText->setPos(txPos, tyPos);

    scene->addItem(titleText);

    // create Play button

}

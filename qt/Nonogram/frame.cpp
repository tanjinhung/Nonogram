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
    QPushButton *PlayButton = new QPushButton(QString("Play"));
    int pbxPos = this->width()/2 - 250;
    int pbyPos = 500;
    PlayButton->setGeometry(pbxPos, pbyPos, 500, 64);
    connect(PlayButton, SIGNAL(clicked()), this, SLOT(showProfileSelectionScreen()));
    scene->addWidget(PlayButton);

    // create Level Editor button
    QPushButton *LevelEditorButton = new QPushButton(QString("Level Editor"));
    int lebxPos = this->width()/2 - 250;
    int lebyPos = 600;
    LevelEditorButton->setGeometry(lebxPos, lebyPos, 500, 64);
    connect(LevelEditorButton, SIGNAL(clicked()), this, SLOT(showLevelEditorScreen()));
    scene->addWidget(LevelEditorButton);
}

void Frame::showProfileSelectionScreen()
{
    scene->clear();



    QPushButton *CreateProfileButton = new QPushButton(QString("Create Profile"));
    int cpbxPos = this->width() - 250 - 16;
    int cpbyPos = this->height() - 36 - 16;
    CreateProfileButton->setGeometry(cpbxPos, cpbyPos, 250, 36);
    scene->addWidget(CreateProfileButton);
}

#include "frame.h"
#include "CSVUserDAO.h"
#include "UserItemWidget.h"
#include "clickablelabel.h"
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QGraphicsGridLayout>
#include <QGraphicsProxyWidget>
#include <iostream>

Frame::Frame(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1600, 900);

    scene->setSceneRect(0, 0, 1600, 900);
    setScene(scene);
}

void Frame::hideCurrentItems() {
    for (auto item : currentItems) {
        item->setVisible(false);
    }
    for (auto widget : currentWidgets) {
        widget->hide();
    }
}

void Frame::showMainMenu() {
    hideCurrentItems();

    // display title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Nonogram"));
    QFont titleFont("Courier New", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 300;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);
    currentItems.append(titleText);

    // create Play button
    QPushButton *PlayButton = new QPushButton(QString("Play"));
    int pbxPos = this->width()/2 - 250;
    int pbyPos = 500;
    PlayButton->setGeometry(pbxPos, pbyPos, 500, 64);
    connect(PlayButton, &QPushButton::clicked, this, &Frame::showProfileSelectionScreen);
    scene->addWidget(PlayButton);
    currentWidgets.append(PlayButton);

    // create Level Editor button
    QPushButton *LevelEditorButton = new QPushButton(QString("Level Editor"));
    int lebxPos = this->width()/2 - 250;
    int lebyPos = 600;
    LevelEditorButton->setGeometry(lebxPos, lebyPos, 500, 64);
    // connect(LevelEditorButton, &QPushButton::clicked, this, &Frame::showLevelEditorScreen);
    scene->addWidget(LevelEditorButton);
    currentWidgets.append(LevelEditorButton);
}

void Frame::showProfileSelectionScreen() {
    hideCurrentItems();

    QListWidget *userList = new QListWidget();
    int ulxPos = this->width()/2 - 750;
    int ulyPos = 32;
    userList->setGeometry(ulxPos, ulyPos, 1500, 800);
    scene->addWidget(userList);
    currentWidgets.append(userList);

    CSVUserDAO userDAO("users.csv");
    std::vector<User> users = userDAO.getAllUsers();

    for (const User &user : users) {
        QListWidgetItem *listItem = new QListWidgetItem(userList);
        UserItemWidget *userWidget = new UserItemWidget(user);

        connect(userWidget, &UserItemWidget::selectUser, this, &Frame::selectUser);
        connect(userWidget, &UserItemWidget::deleteUser, this, &Frame::deleteUser);

        listItem->setSizeHint(userWidget->sizeHint());
        userList->setItemWidget(listItem, userWidget);
    }

    QPushButton *createProfileButton = new QPushButton(QString("Create Profile"));
    int cpbxPos = this->width() - 250 - 16;
    int cpbyPos = this->height() - 36 - 16;
    createProfileButton->setGeometry(cpbxPos, cpbyPos, 250, 36);
    connect(createProfileButton, &QPushButton::clicked, this, &Frame::showProfileCreationOverlay);
    scene->addWidget(createProfileButton);
    currentWidgets.append(createProfileButton);
}

void Frame::showProfileCreationOverlay()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    overlayProfileView = new QGraphicsView(scene, this);
    overlayProfileView->setGeometry(0, 0, this->width(), this->height());
    overlayProfileView->setStyleSheet("background-color: rgba(0, 0, 0, 150);");

    QGraphicsRectItem *whiteBackground = new QGraphicsRectItem();
    whiteBackground->setRect(wbxPos, wbyPos, wbWidth, wbHeight);
    whiteBackground->setBrush(QBrush(Qt::white));
    whiteBackground->setPen(Qt::NoPen);
    scene->addItem(whiteBackground);

    // Hero Image
    heroImageLabel = new QLabel();
    QPixmap heroImagePixmap(QString(":/image/1.png"));
    heroImageLabel->setPixmap(heroImagePixmap.scaled(wbWidth / 2, wbHeight - 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsProxyWidget *heroImageProxy = scene->addWidget(heroImageLabel);
    heroImageProxy->setPos(wbxPos + 32, wbyPos + 32);

    // Input Username
    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter profile name");
    nameInput->setStyleSheet("padding: 2em;");
    nameInput->setFixedWidth(wbWidth /2 - 16);
    int niWidth = nameInput->width();
    QGraphicsProxyWidget *nameInputProxy = scene->addWidget(nameInput);
    nameInputProxy->setPos(wbxPos + 470, wbyPos + 64);


    // TODO: Add a 2x5 grid of images
    QGraphicsWidget *gridContainer = new QGraphicsWidget();
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout();

    gridLayout->setRowSpacing(0, 32);

    // Add images to the grid layout
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            int imageNumber = i * 5 + j + 1; // Calculate image number from 1 to 10
            QString imagePath = QString(":/image/%1.png").arg(imageNumber);
            ClickableLabel *imageLabel = new ClickableLabel();
            imageLabel->setImagePath(imagePath);
            QPixmap imagePixmap(imagePath);

            QPixmap circularPixmap((niWidth - 16) / 5, (niWidth - 16) / 5);
            circularPixmap.fill(Qt::white);

            QPainterPath path;
            path.addEllipse(0, 0, (niWidth - 16) / 5, (niWidth - 16) / 5);

            QPainter painter(&circularPixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setClipPath(path);
            painter.drawPixmap(0, -16, imagePixmap.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            imageLabel->setPixmap(circularPixmap);
            QGraphicsProxyWidget *imageProxy = new QGraphicsProxyWidget();
            imageProxy->setWidget(imageLabel);
            gridLayout->addItem(imageProxy, i, j);

            connect(imageLabel, &ClickableLabel::clicked, this, [this, imageNumber]{
                this->selectedImageNumber = imageNumber;
                updateHeroImage(QString(":/image/%1.png").arg(imageNumber));
            });
        }
    }

    gridContainer->setLayout(gridLayout);
    gridContainer->setPos(wbxPos + 460, wbyPos + 200); // Position the grid below the hero image and input
    scene->addItem(gridContainer);

    // Cancel button
    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setStyleSheet("padding: 1em;");
    cancelButton->setFixedWidth(2 * ((niWidth - 16) / 5));
    connect(cancelButton, &QPushButton::clicked, this, &Frame::destroyProfileOverlay);
    QGraphicsProxyWidget *cancelButtonProxy = scene->addWidget(cancelButton);
    cancelButtonProxy->setPos(wbxPos + 470, wbyPos + 500);

    // Confirm button
    QPushButton *confirmButton = new QPushButton("Confirm");
    confirmButton->setStyleSheet("padding: 1em;");
    confirmButton->setFixedWidth(2 * ((niWidth - 16) / 5));
    connect(confirmButton, &QPushButton::clicked, this, &Frame::showConfirmationOverlay);
    QGraphicsProxyWidget *confirmButtonProxy = scene->addWidget(confirmButton);
    confirmButtonProxy->setPos(wbxPos + 486 + (3 * ((niWidth - 16) / 5)), wbyPos + 500);

    overlayProfileView->show();
}

void Frame::showConfirmationOverlay()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    overlayConfirmationView = new QGraphicsView(scene, this);
    overlayConfirmationView->setGeometry(0, 0, this->width(), this->height());
    overlayConfirmationView->setStyleSheet("background-color: rgba(0, 0, 0, 150);");

    QGraphicsRectItem *confirmBackground = new QGraphicsRectItem();
    confirmBackground->setRect(wbxPos - 250, wbyPos - 150, wbWidth / 2, wbHeight / 2);
    confirmBackground->setBrush(QBrush(Qt::white));
    confirmBackground->setPen(Qt::NoPen);
    scene->addItem(confirmBackground);

    QGraphicsTextItem *confirmationText = new QGraphicsTextItem("Confirm Profile Creation!");
    QFont confirmationFont("Arial", 24);
    confirmationText->setFont(confirmationFont);
    confirmationText->setPos(wbxPos - 175, wbyPos - 50);
    scene->addItem(confirmationText);

    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setStyleSheet("padding: 1em;");
    cancelButton->setFixedWidth(200);
    connect(cancelButton, &QPushButton::clicked, this, &Frame::destroyOverlay);
    QGraphicsProxyWidget *cancelButtonProxy = scene->addWidget(cancelButton);
    cancelButtonProxy->setPos(wbxPos - 225, wbyPos + 50);

    QPushButton *confirmButton = new QPushButton("Confirm");
    confirmButton->setStyleSheet("padding: 1em;");
    confirmButton->setFixedWidth(200);
    connect(confirmButton, &QPushButton::clicked, this, [this]{
        emit registerUser(nameInput->text(), selectedImageNumber);
    });
    QGraphicsProxyWidget *confirmButtonProxy = scene->addWidget(confirmButton);
    confirmButtonProxy->setPos(wbxPos + 25, wbyPos + 50);

    overlayConfirmationView->show();
}

void Frame::selectUser(int userId) {
    // Handle user selection
    std::cout << "Selected User ID: " << userId << std::endl;
}

void Frame::deleteUser(int userId) {
    // Handle user deletion
    CSVUserDAO userDAO("users.csv");
    userDAO.deleteUser(userId);

    // Refresh the profile selection screen
    showProfileSelectionScreen();
}

void Frame::destroyProfileOverlay()
{
    overlayProfileView->hide();
}

void Frame::destroyConfirmationOverlay()
{
    overlayConfirmationView->hide();
}

void Frame::destroyOverlay()
{
    destroyProfileOverlay();
    destroyConfirmationOverlay();
}

void Frame::updateHeroImage(const QString &imagePath)
{
    QPixmap newPixmap(imagePath);
    heroImageLabel->setPixmap(newPixmap.scaled(wbWidth / 2, wbHeight - 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Frame::handleRegistrationFailure(const QString &message)
{
    destroyConfirmationOverlay();

    nameInput->setStyleSheet("border: 2px red solid;padding: 2em;");
    QGraphicsTextItem *warningText = new QGraphicsTextItem(message);
    QFont warningFont("Arial", 12);
    warningText->setFont(warningFont);
    warningText->setDefaultTextColor(Qt::red);
    QGraphicsProxyWidget *nameInputProxy = scene->addWidget(nameInput);
    nameInputProxy->setPos(nameInput->x(), nameInput->y() + nameInput->height() + 16);
    scene->addItem(warningText);
}

void Frame::handleRegistrationSuccess()
{
    destroyOverlay();
    showProfileSelectionScreen();
}

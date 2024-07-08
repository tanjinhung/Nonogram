#include "frame.h"
#include "CSVUserDAO.h"
#include "UserItemWidget.h"
#include "clickablelabel.h"
#include "customscrollarea.h"
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QGraphicsGridLayout>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QAbstractScrollArea>
#include <QScrollArea>
#include <QScrollBar>
#include <QTime>
#include <QHBoxLayout>

Frame::Frame(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1600, 900);

    scene->setSceneRect(0, 0, 1600, 900);
    setScene(scene);
}

void Frame::hideCurrentItems()
{
    for (auto item : currentItems) {
        item->setVisible(false);
    }
    for (auto widget : currentWidgets) {
        widget->hide();
    }
}

void Frame::showMainMenu()
{
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

void Frame::showProfileSelectionScreen()
{
    hideCurrentItems();

    CustomScrollArea *scrollArea = new CustomScrollArea();
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);

    CSVUserDAO userDAO("users.csv");
    std::vector<User> users = userDAO.getAllUsers();

    for (const User &user : users)
    {
        UserItemWidget *userWidget = new UserItemWidget(user);

        connect(userWidget, &UserItemWidget::selectUser, this, &Frame::selectUser);
        connect(userWidget, &UserItemWidget::deleteUser, this, &Frame::deleteUser);

        layout->addWidget(userWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(false);
    scrollArea->setGeometry(this->width() / 2 - 700, 32, 1350, 800);
    scene->addWidget(scrollArea);
    currentWidgets.append(scrollArea);

    // Back Button
    QPushButton *backButton = new QPushButton(QString("Back"));
    int bbxPos = 32;
    int bbyPos = this->height() - 48;
    backButton->setGeometry(bbxPos, bbyPos, 250, 32);
    connect(backButton, &QPushButton::clicked, this, &Frame::showMainMenu);
    scene->addWidget(backButton);
    currentWidgets.append(backButton);

    // Create Profile Button
    QPushButton *createProfileButton = new QPushButton(QString("Create Profile"));
    int cpbxPos = this->width() - 266;
    int cpbyPos = this->height() - 48;
    createProfileButton->setGeometry(cpbxPos, cpbyPos, 250, 32);
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
    nameInputProxy = scene->addWidget(nameInput);
    nameInputProxy->setPos(wbxPos + 470, wbyPos + 64);

    // Add a error message box
    errorMsgLabel = new QLabel("");
    errorMsgLabel->setStyleSheet("background-color:transparent; color: red");
    errorMsgLabel->setVisible(false);
    errorMsgLabelProxy = scene->addWidget(errorMsgLabel);
    errorMsgLabelProxy->setPos(wbxPos + 470, wbyPos + 150);

    // Add a 2x5 grid of images
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

void Frame::showDifficultySelectionScreen()
{
    hideCurrentItems();

    QGraphicsTextItem *difficultyTitle = new QGraphicsTextItem("Difficulty");
    QFont difficultyFont("Courier New", 36);
    difficultyTitle->setFont(difficultyFont);
    difficultyTitle->setPos(this->width() / 2 - difficultyTitle->boundingRect().width() / 2, 64);
    scene->addItem(difficultyTitle);
    currentItems.append(difficultyTitle);

    QGraphicsWidget *gridContainer = new QGraphicsWidget();
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout();

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            int numDifficulty = i * 3 + j;
            QString difficulty = QString("%1").arg(difficulties[numDifficulty]);
            QPushButton *difficultyButton = new QPushButton(difficulty);
            difficultyButton->setStyleSheet("padding: 2em;");
            difficultyButton->setFixedWidth(400);
            connect(difficultyButton, &QPushButton::clicked, [difficulty] {
                qDebug() << "Selected difficulty:" << difficulty;
            });
            QGraphicsProxyWidget *difficultyButtonProxy = new QGraphicsProxyWidget();
            difficultyButtonProxy->setWidget(difficultyButton);
            gridLayout->addItem(difficultyButtonProxy, j, i);
            gridLayout->setColumnSpacing(i, 64);
            gridLayout->setRowSpacing(j, 64);
        }
    }

    gridContainer->setLayout(gridLayout);
    gridContainer->setPos(this->width() / 2 - 432, 200); // Position the grid below the hero image and input
    scene->addItem(gridContainer);
    currentItems.append(gridContainer);

    // Back Button
    QPushButton *backButton = new QPushButton(QString("Back"));
    int bbxPos = 32;
    int bbyPos = this->height() - 48;
    backButton->setGeometry(bbxPos, bbyPos, 250, 32);
    connect(backButton, &QPushButton::clicked, this, &Frame::showMainMenu);
    scene->addWidget(backButton);
    currentWidgets.append(backButton);

    // TODO: HighScore
    QPushButton *createProfileButton = new QPushButton(QString("Highscore"));
    int cpbxPos = this->width() - 266;
    int cpbyPos = this->height() - 48;
    createProfileButton->setGeometry(cpbxPos, cpbyPos, 250, 32);
    // connect(createProfileButton, &QPushButton::clicked, this, &Frame::showProfileCreationOverlay);
    scene->addWidget(createProfileButton);
    currentWidgets.append(createProfileButton);
}

void Frame::selectUser(int userId)
{
    // Handle user selection
    currentUserId = userId;
    startTime = QTime::currentTime();
    qDebug() << "Current User ID: " << currentUserId;
    qDebug() << "Current Time: " << startTime.toString();
    showDifficultySelectionScreen();
}

void Frame::deleteUser(int userId)
{
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
    qDebug() << "The following message is passed:" << message;
    destroyConfirmationOverlay();

    nameInput->setStyleSheet("border: 2px solid red; padding: 2em;");

    errorMsgLabel->setText(message);
    errorMsgLabel->setVisible(true);
}

void Frame::handleRegistrationSuccess()
{
    destroyOverlay();
    showProfileSelectionScreen();
}

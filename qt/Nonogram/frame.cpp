#include "frame.h"
#include "CSVUserDAO.h"
#include "UserItemWidget.h"
#include "clickablelabel.h"
#include "customscrollarea.h"
#include "customtile.h"
#include "difficulty.h"
#include "csvscoredao.h"
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
#include <QTimer>
#include <QApplication>

Frame::Frame(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1600, 900);

    scene->setSceneRect(0, 0, 1600, 900);
    setScene(scene);

    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, [this]{
        int timeElapsed = startTime.msecsTo(QTime::currentTime());
        qDebug() << "Time Diffrence: " << timeElapsed;
        emit updateTotalTimePlayed(currentUserId, timeElapsed);
    });
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

    // Display Title Text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Nonogram"));
    QFont titleFont("Courier New", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 300;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);
    currentItems.append(titleText);

    // Create Play button
    QPushButton *PlayButton = new QPushButton(QString("Play"));
    int pbxPos = this->width()/2 - 250;
    int pbyPos = 500;
    PlayButton->setGeometry(pbxPos, pbyPos, 500, 64);
    connect(PlayButton, &QPushButton::clicked, this, &Frame::showProfileSelectionScreen);
    scene->addWidget(PlayButton);
    currentWidgets.append(PlayButton);

    // Create Level Editor button
    QPushButton *LevelEditorButton = new QPushButton(QString("Level Editor"));
    int lebxPos = this->width()/2 - 250;
    int lebyPos = 600;
    LevelEditorButton->setGeometry(lebxPos, lebyPos, 500, 64);
    connect(LevelEditorButton, &QPushButton::clicked, this, [this]{
        emit createLevelEditor(Flag::EDITING);
    });
    scene->addWidget(LevelEditorButton);
    currentWidgets.append(LevelEditorButton);

    // Create Exit button
    QPushButton *exitButton = new QPushButton("Exit");
    exitButton->setGeometry(this->width()/2-250, 700, 500, 64);
    connect(exitButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
    scene->addWidget(exitButton);
    currentWidgets.append(exitButton);
}

void Frame::showProfileSelectionScreen()
{
    hideCurrentItems();

    // Display the users
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

    // Create Back button
    QPushButton *backButton = new QPushButton(QString("Back"));
    int bbxPos = 32;
    int bbyPos = this->height() - 48;
    backButton->setGeometry(bbxPos, bbyPos, 250, 32);
    connect(backButton, &QPushButton::clicked, this, &Frame::showMainMenu);
    scene->addWidget(backButton);
    currentWidgets.append(backButton);

    // Create Profile button
    QPushButton *createProfileButton = new QPushButton(QString("Create Profile"));
    int cpbxPos = this->width() - 282;
    int cpbyPos = this->height() - 48;
    createProfileButton->setGeometry(cpbxPos, cpbyPos, 250, 32);
    connect(createProfileButton, &QPushButton::clicked, this, &Frame::showProfileCreationOverlay);
    scene->addWidget(createProfileButton);
    currentWidgets.append(createProfileButton);
}

void Frame::showLevelEditorScreen(EditorLevel *editorLevel)
{
    hideCurrentItems();

    qDebug() << "Showing Level Editor Screen";

    // Create Play Grid
    QGraphicsWidget *gridContainer = new QGraphicsWidget();
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout(gridContainer);

    int size = editorLevel->getSize();

    // Add row and column hints
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Add the game tiles
            CustomTile *tile = new CustomTile(i, j);
            gridLayout->addItem(tile, i + 1, j + 1);

            connect(tile, &CustomTile::leftButtonClicked, this, [this, tile]() {
                emit registerTileClicked(0, tile);
            });

            connect(tile, &CustomTile::middleButtonClicked, this, [this, tile]() {
                emit registerTileClicked(2, tile);
            });

            connect(tile, &CustomTile::rightButtonClicked, this, [this, tile]() {
                emit registerTileClicked(1, tile);
            });
        }
    }

    gridLayout->setParentLayoutItem(gridContainer);
    gridContainer->setGeometry(
        this->width() / 2 - 400,
        this->height() / 2 - 450,
        800, 800);
    scene->addItem(gridContainer);
    currentItems.append(gridContainer);

    // Back button
    QPushButton *backButton = new QPushButton(QString("Back"));
    backButton->setGeometry(32, this->height() - 48, 250, 32);
    connect(backButton, &QPushButton::clicked, this, [this]{
        showMainMenu();
        emit updateEditorFlag(Flag::DEFAULT);
    });
    scene->addWidget(backButton);
    currentWidgets.append(backButton);

    // Clear button
    QPushButton *clearButton = new QPushButton(QString("Clear"));
    clearButton->setGeometry(460, this->height() - 48, 250, 32);
    connect(clearButton, &QPushButton::clicked, this, [this, gridContainer]{
        qDebug() << "Clearing the grid...";
        for (QGraphicsItem *items:gridContainer->childItems()) {
            CustomTile *tile = dynamic_cast<CustomTile *>(items);
            if (tile) {
                tile->setColor(Qt::white);
            }
        }
        emit clearGrid();
    });
    scene->addWidget(clearButton);
    currentWidgets.append(clearButton);

    // Resize button
    QPushButton *resizeButton = new QPushButton(QString("Resize"));
    resizeButton->setGeometry(890, this->height() - 48, 250, 32);
    connect(resizeButton, &QPushButton::clicked, this, [this]{
        showDifficultySelectionScreen();
    });
    scene->addWidget(resizeButton);
    currentWidgets.append(resizeButton);

    // Publish button
    QPushButton *publishButton = new QPushButton(QString("Publish"));
    publishButton->setGeometry(this->width() - 282, this->height() - 48, 250, 32);
    connect(publishButton, &QPushButton::clicked, this, [this]{
        emit publishLevel();
        showMainMenu();
    });
    scene->addWidget(publishButton);
    currentWidgets.append(publishButton);
}

void Frame::showProfileCreationOverlay()
{
    // Creating the overlay
    QGraphicsScene *scene = new QGraphicsScene(this);
    overlayProfileView = new QGraphicsView(scene, this);
    overlayProfileView->setGeometry(0, 0, this->width(), this->height());
    overlayProfileView->setStyleSheet("background-color: rgba(0, 0, 0, 150);");

    QGraphicsRectItem *whiteBackground = new QGraphicsRectItem();
    whiteBackground->setRect(wbxPos, wbyPos, wbWidth, wbHeight);
    whiteBackground->setBrush(QBrush(palette().color(QPalette::Window)));
    whiteBackground->setPen(Qt::NoPen);
    scene->addItem(whiteBackground);

    // Hero Image
    heroImageLabel = new QLabel();
    QPixmap heroImagePixmap(QString(":/image/1.png"));
    heroImageLabel->setPixmap(heroImagePixmap.scaled(
        wbWidth / 2, wbHeight - 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
            circularPixmap.fill(Qt::transparent);

            QPainterPath path;
            path.addEllipse(0, 0, (niWidth - 16) / 5, (niWidth - 16) / 5);

            QPainter painter(&circularPixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setClipPath(path);
            painter.drawPixmap(
                0, -16, imagePixmap.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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
    gridContainer->setPos(wbxPos + 460, wbyPos + 200);
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
    connect(confirmButton, &QPushButton::clicked, this, [this]{
        showConfirmationOverlay("Confirm Profile Creation!", [this]{
            emit registerUser(nameInput->text(), selectedImageNumber);
        });
    });
    QGraphicsProxyWidget *confirmButtonProxy = scene->addWidget(confirmButton);
    confirmButtonProxy->setPos(wbxPos + 486 + (3 * ((niWidth - 16) / 5)), wbyPos + 500);

    overlayProfileView->show();
}

void Frame::showConfirmationOverlay(const QString &message, std::function<void ()> onConfirm)
{
    // Creating the overlay
    QGraphicsScene *scene = new QGraphicsScene(this);
    overlayConfirmationView = new QGraphicsView(scene, this);
    overlayConfirmationView->setGeometry(0, 0, this->width(), this->height());
    overlayConfirmationView->setStyleSheet("background-color: rgba(0, 0, 0, 150);");

    // Add a background
    QGraphicsRectItem *confirmBackground = new QGraphicsRectItem();
    confirmBackground->setRect(wbxPos - 250, wbyPos - 150, wbWidth / 2, wbHeight / 2);
    confirmBackground->setBrush(QBrush(palette().color(QPalette::Window)));
    confirmBackground->setPen(Qt::NoPen);
    scene->addItem(confirmBackground);

    // Add the text
    QGraphicsTextItem *confirmationText = new QGraphicsTextItem(message);
    QFont confirmationFont("Arial", 24);
    confirmationText->setFont(confirmationFont);
    confirmationText->setPos(wbxPos - 175, wbyPos - 50);
    scene->addItem(confirmationText);

    // Cancel button
    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setStyleSheet("padding: 1em;");
    cancelButton->setFixedWidth(200);
    connect(cancelButton, &QPushButton::clicked, this, &Frame::destroyOverlay);
    QGraphicsProxyWidget *cancelButtonProxy = scene->addWidget(cancelButton);
    cancelButtonProxy->setPos(wbxPos - 225, wbyPos + 50);

    // Confirm button
    QPushButton *confirmButton = new QPushButton("Confirm");
    confirmButton->setStyleSheet("padding: 1em;");
    confirmButton->setFixedWidth(200);
    connect(confirmButton, &QPushButton::clicked, this, [onConfirm]{
        onConfirm();
    });
    QGraphicsProxyWidget *confirmButtonProxy = scene->addWidget(confirmButton);
    confirmButtonProxy->setPos(wbxPos + 25, wbyPos + 50);

    overlayConfirmationView->show();
}

void Frame::showDifficultySelectionScreen()
{
    hideCurrentItems();

    // Display title text
    QGraphicsTextItem *difficultyTitle = new QGraphicsTextItem("Difficulty");
    QFont difficultyFont("Courier New", 36);
    difficultyTitle->setFont(difficultyFont);
    difficultyTitle->setPos(this->width() / 2 - difficultyTitle->boundingRect().width() / 2, 64);
    scene->addItem(difficultyTitle);
    currentItems.append(difficultyTitle);

    // Create the Difficulty grid
    QGraphicsWidget *gridContainer = new QGraphicsWidget();
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout();

    std::vector<Difficulty> difficulties = {Difficulty::Easy,
                                            Difficulty::Normal,
                                            Difficulty::Hard,
                                            Difficulty::Extreme,
                                            Difficulty::Hell,
                                            Difficulty::Custom};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            int numDifficulty = i * 3 + j;
            if (numDifficulty >= int(difficulties.size())) break;
            Difficulty difficulty = difficulties[numDifficulty];
            QPushButton *difficultyButton = new QPushButton(difficultyToString(difficulty));
            difficultyButton->setStyleSheet("padding: 2em;");
            difficultyButton->setFixedWidth(400);
            connect(difficultyButton, &QPushButton::clicked, this, [this, difficulty] {
                qDebug() << "Selected difficulty:" << difficultyToString(difficulty);
                currentDifficulty = difficulty;
                emit registerDifficulty(currentDifficulty);
            });
            QGraphicsProxyWidget *difficultyButtonProxy = new QGraphicsProxyWidget();
            difficultyButtonProxy->setWidget(difficultyButton);
            gridLayout->addItem(difficultyButtonProxy, j, i);
            gridLayout->setColumnSpacing(i, 64);
            gridLayout->setRowSpacing(j, 64);
        }
    }

    gridContainer->setLayout(gridLayout);
    gridContainer->setPos(this->width() / 2 - 432, 300);
    scene->addItem(gridContainer);
    currentItems.append(gridContainer);

    // Back Button
    QPushButton *backButton = new QPushButton(QString("Back"));
    int bbxPos = 32;
    int bbyPos = this->height() - 48;
    backButton->setGeometry(bbxPos, bbyPos, 250, 32);
    connect(backButton, &QPushButton::clicked, this, [this] {
        int timeElapsed = startTime.msecsTo(QTime::currentTime());
        qDebug() << "Time Diffrence: " << timeElapsed;
        emit updateTotalTimePlayed(currentUserId, timeElapsed);
        showProfileSelectionScreen();
    });
    scene->addWidget(backButton);
    currentWidgets.append(backButton);

    // HighScore Button
    QPushButton *createProfileButton = new QPushButton(QString("Highscore"));
    int cpbxPos = this->width() - 282;
    int cpbyPos = this->height() - 48;
    createProfileButton->setGeometry(cpbxPos, cpbyPos, 250, 32);
    connect(createProfileButton, &QPushButton::clicked, this, &Frame::showHighscoreOverlay);
    scene->addWidget(createProfileButton);
    currentWidgets.append(createProfileButton);
}

void Frame::showPlayScreen(const Level &level)
{
    hideCurrentItems();

    qDebug() << "Showing Play Screen";

    // Create Play Grid
    QGraphicsWidget *gridContainer = new QGraphicsWidget();
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout(gridContainer);

    int size = level.getSize();
    const std::vector<std::vector<int>> &rowHint = level.getRowHint();
    const std::vector<std::vector<int>> &colHint = level.getColHint();

    // Add row and column hints
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == 0) {
                // Add column hints
                QString hintText;
                for (int k = 0; k < static_cast<int>(colHint[j].size()); ++k) {
                    hintText += QString::number(colHint[j][k]);
                    if (k != static_cast<int>(colHint[j].size()) - 1) {
                        hintText += "\n";
                    }
                }
                QLabel *hintLabel = new QLabel(hintText.trimmed());
                hintLabel->setStyleSheet("background-color: transparent");
                hintLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
                QGraphicsProxyWidget *hintLabelProxy = new QGraphicsProxyWidget();
                hintLabelProxy->setWidget(hintLabel);
                gridLayout->addItem(hintLabelProxy, 0, j + 1);
            }
            if (j == 0) {
                // Add row hints
                QString hintText;
                for (int hint : rowHint[i]) {
                    hintText += QString::number(hint) + " ";
                }
                QLabel *hintLabel = new QLabel(hintText.trimmed());
                hintLabel->setStyleSheet("background-color: transparent");
                hintLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
                QGraphicsProxyWidget *hintLabelProxy = new QGraphicsProxyWidget();
                hintLabelProxy->setWidget(hintLabel);
                gridLayout->addItem(hintLabelProxy, i + 1, 0);
            }
            // Add the game tiles
            CustomTile *tile = new CustomTile(i, j);
            gridLayout->addItem(tile, i + 1, j + 1);

            connect(tile, &CustomTile::leftButtonClicked, this, [this, tile]() {
                emit registerTileClicked(0, tile);
            });

            connect(tile, &CustomTile::middleButtonClicked, this, [this, tile]() {
                emit registerTileClicked(2, tile);
            });

            connect(tile, &CustomTile::rightButtonClicked, this, [this, tile]() {
                emit registerTileClicked(1, tile);
            });
        }
    }

    gridLayout->setParentLayoutItem(gridContainer);
    gridContainer->setGeometry(
        this->width() / 2 - 400,
        this->height() / 2 - 450,
        800, 800);
    scene->addItem(gridContainer);
    currentItems.append(gridContainer);

    // Back button
    QPushButton *backButton = new QPushButton(QString("Back"));
    backButton->setGeometry(32, this->height() - 48, 250, 32);
    connect(backButton, &QPushButton::clicked, this, [this]{
        showDifficultySelectionScreen();
    });
    scene->addWidget(backButton);
    currentWidgets.append(backButton);

    // Clear button
    QPushButton *clearButton = new QPushButton(QString("Clear"));
    clearButton->setGeometry(460, this->height() - 48, 250, 32);
    connect(clearButton, &QPushButton::clicked, this, [this, gridContainer, level]{
        qDebug() << "Clearing the grid...";
        for (QGraphicsItem *items:gridContainer->childItems()) {
            CustomTile *tile = dynamic_cast<CustomTile *>(items);
            if (tile) {
                tile->setColor(Qt::white);
            }
        }
        emit clearGrid();
    });
    scene->addWidget(clearButton);
    currentWidgets.append(clearButton);

    // Reset button
    QPushButton *resetButton = new QPushButton(QString("Reset"));
    resetButton->setGeometry(890, this->height() - 48, 250, 32);
    connect(resetButton, &QPushButton::clicked, this, [this, resetButton]{
        resetButton->setEnabled(false);
        emit registerDifficulty(currentDifficulty);
        QTimer::singleShot(200, resetButton, [resetButton](){
            resetButton->setEnabled(true);
        });
    });
    scene->addWidget(resetButton);
    currentWidgets.append(resetButton);

    // Finish button
    QPushButton *finishButton = new QPushButton(QString("Finish"));
    finishButton->setGeometry(this->width() - 282, this->height() - 48, 250, 32);
    connect(finishButton, &QPushButton::clicked, this, [this]{
        emit registerFinishGame();
    });
    scene->addWidget(finishButton);
    currentWidgets.append(finishButton);
}

void Frame::showFinishOverlay(
    const QString &message,
    const QString &acceptMsg,
    std::function<void ()> onAccept)
{
    // Creating the overlay
    QGraphicsScene *scene = new QGraphicsScene(this);
    overlayFinishView = new QGraphicsView(scene, this);
    overlayFinishView->setGeometry(0, 0, this->width(), this->height());
    overlayFinishView->setStyleSheet("background-color: rgba(0, 0, 0, 150);");

    // Add a background
    QGraphicsRectItem *finishBackground = new QGraphicsRectItem();
    finishBackground->setRect(wbxPos - 250, wbyPos - 150, wbWidth / 2, wbHeight / 2);
    finishBackground->setBrush(QBrush(palette().color(QPalette::Window)));
    finishBackground->setPen(Qt::NoPen);
    scene->addItem(finishBackground);

    // Add the text
    QGraphicsTextItem *finishText = new QGraphicsTextItem(message);
    QFont confirmationFont("Arial", 24);
    finishText->setFont(confirmationFont);
    finishText->setPos(-finishBackground->boundingRect().width()/2, wbyPos - 50);
    scene->addItem(finishText);

    // Exit button
    QPushButton *exitButton = new QPushButton("Cancel");
    exitButton->setStyleSheet("padding: 1em;");
    exitButton->setFixedWidth(200);
    connect(exitButton, &QPushButton::clicked, this, [this]{
        showDifficultySelectionScreen();
        destroyFinishOverlay();
    });
    QGraphicsProxyWidget *exitButtonProxy = scene->addWidget(exitButton);
    exitButtonProxy->setPos(wbxPos - 225, wbyPos + 50);

    // Accept button
    QPushButton *acceptButton = new QPushButton(acceptMsg);
    acceptButton->setStyleSheet("padding: 1em;");
    acceptButton->setFixedWidth(200);
    connect(acceptButton, &QPushButton::clicked, this, [onAccept]{
        onAccept();
    });
    QGraphicsProxyWidget *acceptButtonProxy = scene->addWidget(acceptButton);
    acceptButtonProxy->setPos(wbxPos + 25, wbyPos + 50);

    overlayFinishView->show();
}

void Frame::showHighscoreOverlay()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    overlayHighscoreView = new QGraphicsView(scene, this);
    overlayHighscoreView->setGeometry(0, 0, this->width(), this->height());
    overlayHighscoreView->setStyleSheet("background-color: rgba(0, 0, 0, 150);");

    QGraphicsRectItem *highscoreBackground = new QGraphicsRectItem();
    highscoreBackground->setRect(
        this->width() / 2 - 250,
        this->height() / 2 - 400,
        500, 800);
    highscoreBackground->setBrush(QBrush(palette().color(QPalette::Window)));
    highscoreBackground->setPen(Qt::NoPen);
    scene->addItem(highscoreBackground);

    CSVScoreDAO scoreDAO("score.csv");
    std::vector<Score> scores = scoreDAO.getAllScores();
    std::vector<Score> sortedScores = scores;

    std::sort(sortedScores.begin(),
              sortedScores.end(),
              [](const Score& a, const Score& b) {
        QString diffA = a.getLevelDifficulty();
        QString diffB = b.getLevelDifficulty();
        if (diffA == diffB) {
            return a.getCompletionTime() < b.getCompletionTime();
        }
        return diffA < diffB;
    });

    // Create the QTabWidget
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->setGeometry(0, 0, 468, 700);
    tabWidget->setStyleSheet("QTabBar::tab { width: 93px; }");

    // Create a map to store tabs and layouts for each difficulty
    QMap<QString, QWidget*> tabMap;
    QMap<QString, QVBoxLayout*> layoutMap;

    // List of Difficulty enum values
    Difficulty difficulties[] = {Difficulty::Easy,
                                 Difficulty::Normal,
                                 Difficulty::Hard,
                                 Difficulty::Extreme,
                                 Difficulty::Hell};

    // Iterate through the Difficulty enum values to create tabs
    for (Difficulty diff : difficulties) {
        QString diffStr = difficultyToString(diff);
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);

        tabMap.insert(diffStr, tab);
        layoutMap.insert(diffStr, layout);

        QWidget *scrollAreaWidget = new QWidget();
        layout->setAlignment(Qt::AlignTop);
        scrollAreaWidget->setLayout(layout);
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setWidget(scrollAreaWidget);
        scrollArea->setWidgetResizable(true);

        QVBoxLayout *tabLayout = new QVBoxLayout(tab);
        tabLayout->addWidget(scrollArea);

        tabWidget->addTab(tab, diffStr);
    }

    for (const Score &score : sortedScores) {
        QString diff = score.getLevelDifficulty();
        if (layoutMap.contains(diff)) {
            QString timeString = QTime(0, 0, 0)
                                     .addMSecs(score.getCompletionTime())
                                     .toString("hh:mm:ss.zzz");

            QWidget *scoreWidget = new QWidget();
            QHBoxLayout *scoreLayout = new QHBoxLayout(scoreWidget);

            QLabel *playerNameLabel = new QLabel(score.getUserName());
            QLabel *completionTimeLabel = new QLabel(timeString);

            playerNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            completionTimeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

            scoreLayout->addWidget(playerNameLabel);
            scoreLayout->addWidget(completionTimeLabel);
            scoreLayout->setContentsMargins(0, 0, 0, 0);

            scoreWidget->setFixedHeight(32);
            scoreWidget->setStyleSheet("border-bottom: 1px solid black");
            layoutMap[diff]->addWidget(scoreWidget);
        }
    }

    for (auto it = layoutMap.begin(); it != layoutMap.end(); ++it) {
        if (it.value()->isEmpty()) {
            QLabel *noScoresLabel = new QLabel("No scores yet");
            noScoresLabel->setFixedHeight(32);
            it.value()->addWidget(noScoresLabel);
        }
    }

    QGraphicsProxyWidget *tabWidgetProxy= scene->addWidget(tabWidget);
    tabWidgetProxy->setPos(this->width() / 2 - 234, this->height() / 2 - 368);

    QPushButton *closeButton = new QPushButton("Close");
    closeButton->setGeometry(this->width() / 2 - 125, this->height() - 96, 250, 32);
    connect(closeButton, &QPushButton::clicked, this, &Frame::destroyHighscoreOverlay);
    scene->addWidget(closeButton);

    overlayHighscoreView->show();
}

void Frame::selectUser(int userId)
{
    // Handle user selection
    currentUserId = userId;
    startTime = QTime::currentTime();
    showDifficultySelectionScreen();
}

void Frame::deleteUser(int userId)
{
    // Handle user deletion
    showConfirmationOverlay("Confirm Profile Deletion!", [this, userId]{
        // Handle user deletion
        emit confirmUserDeletion(userId);
        // Destroy Confirmation Overlay
        destroyConfirmationOverlay();
        // Refresh the profile selection screen
        showProfileSelectionScreen();
    });
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

void Frame::destroyFinishOverlay()
{
    overlayFinishView->hide();
}

void Frame::destroyHighscoreOverlay()
{
    overlayHighscoreView->hide();
}

void Frame::updateHeroImage(const QString &imagePath)
{
    QPixmap newPixmap(imagePath);
    heroImageLabel->setPixmap(
        newPixmap.scaled(wbWidth / 2, wbHeight - 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Frame::handleRegistrationFailure(const QString &message)
{
    // Handle Failures
    destroyConfirmationOverlay();

    nameInput->setStyleSheet("border: 2px solid red; padding: 2em;");

    errorMsgLabel->setText(message);
    errorMsgLabel->setVisible(true);
}

void Frame::handleRegistrationSuccess()
{
    // Handle Success
    destroyOverlay();
    showProfileSelectionScreen();
}

void Frame::handleLevelCreated(const Level &level)
{
    showPlayScreen(level);
}

void Frame::handleLevelEditorCreated(EditorLevel &editorLevel)
{
    showLevelEditorScreen(&editorLevel);
}

void Frame::handleLevelChecked(bool result)
{
    qDebug() << "Checked result: " << result;
    if (result) {
        emit registerScore(currentUserId);
        showFinishOverlay("You Win!", "Again", [this]{
            registerDifficulty(currentDifficulty);
            destroyFinishOverlay();
        });
    } else {
        showFinishOverlay("Try Again!", "Retry", [this]{
            destroyFinishOverlay();
            emit resumeGameTimer();
        });
    }
}

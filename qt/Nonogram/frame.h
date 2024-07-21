#ifndef FRAME_H
#define FRAME_H

#include "editorlevel.h"
#include "level.h"
#include "difficulty.h"
#include "editorflag.h"
#include "customtile.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QTime>

class Frame : public QGraphicsView
{
    Q_OBJECT
public:
    Frame(QWidget *parent = nullptr);

    void showMainMenu();
    void showProfileSelectionScreen();
    void showLevelEditorScreen(EditorLevel *editorLevel);
    void showLevelNameOverlay();
    void showProfileCreationOverlay();
    void showConfirmationOverlay(
        const QString &message,
        std::function<void()> onConfirm);
    void showDifficultySelectionScreen();
    void showPlayScreen(const Level &level);
    void showFinishOverlay(
        const QString &message,
        const QString &acceptMsg ,
        std::function<void()> onAccept);
    void showHighscoreOverlay();
    void showCustomLevelScreen();

    QGraphicsScene* scene;

signals:
    void registerUser(const QString &name, int imageNumber);
    void updateTotalTimePlayed(int currentUserId, int timeElapsed);
    void confirmUserDeletion(int userId);
    void registerDifficulty(Difficulty difficulty);
    void registerTileClicked(int button, CustomTile *tile);
    void registerFinishGame();
    void clearGrid();
    void resumeGameTimer();
    void registerScore(int currentUserId);
    void createLevelEditor(Flag flag);
    void updateEditorFlag(Flag flag);
    void publishLevel();
    void registerLevelName(QString levelName);

public slots:
    void handleRegistrationFailure(const QString &message);
    void handleRegistrationSuccess();
    void handleLevelCreated(const Level &level);
    void handleLevelEditorCreated(EditorLevel &editorLevel);
    void handleLevelChecked(bool result);
    void handleCustomLevel();

private slots:
    void selectUser(int userId);
    void deleteUser(int userId);
    void destroyProfileOverlay();
    void destroyConfirmationOverlay();
    void destroyOverlay();
    void destroyFinishOverlay();
    void destroyHighscoreOverlay();
    void destroyLevelNameOverlay();
    void updateHeroImage(const QString &imagePath);


private:
    QList<QGraphicsItem*> currentItems;
    QList<QWidget*> currentWidgets;
    QLabel *heroImageLabel;
    QGraphicsView *overlayProfileView;
    QGraphicsView *overlayConfirmationView;
    QGraphicsView *overlayFinishView;
    QGraphicsView *overlayHighscoreView;
    QGraphicsView *overlayLevelNameView;
    QLineEdit *nameInput;
    QGraphicsProxyWidget *nameInputProxy;
    QLineEdit *levelNameInput;
    QLabel *errorMsgLabel;
    QGraphicsProxyWidget *errorMsgLabelProxy;

    int selectedImageNumber = 1;

    QTime startTime;
    int currentUserId;

    Difficulty currentDifficulty;

    void hideCurrentItems();
};

#endif // FRAME_H

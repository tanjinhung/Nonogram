#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "difficulty.h"
#include "editorflag.h"
#include "level.h"
#include "customtile.h"
#include "user.h"
#include "editorlevel.h"
#include <QObject>
#include <QElapsedTimer>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);

signals:
    void levelCreated(const Level &level);
    void levelEditorCreated(EditorLevel *editorLevel);
    void levelChecked(bool result);
    void getCurrentUser(int userId);

public slots:
    void handleDifficulty(Difficulty difficulty, Flag flag);
    void handleTileClicked(int button, CustomTile *tile);
    void handleFinishGame();
    void handleClearGrid();
    void resumeTimer();
    void registerScore(int userId);
    void handleReturnUser(User user);
    void createLevelEditor();

private:
    Difficulty currentDifficulty;
    Level generatePuzzle(Difficulty difficulty);
    Level newLevel;
    EditorLevel *editorLevel;
    QElapsedTimer playTimer;
    qint64 elapsedPausedTime;
    bool isTimerRunning;
    User currentUser;

    void generateLevel();
    void createLevelEditor(Difficulty difficulty);
};

#endif // GAMECONTROLLER_H

#include "frame.h"
#include "profilecontroller.h"
#include "gamecontroller.h"

#include <QApplication>

Frame *frame;
ProfileController *pController;
GameController *gController;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    frame = new Frame();
    pController = new ProfileController();
    gController = new GameController();

    // frame <-> pController
    QObject::connect(frame, &Frame::registerUser, pController, &ProfileController::registerUser);
    QObject::connect(frame, &Frame::updateTotalTimePlayed, pController, &ProfileController::updateTotalTimePlayed);
    QObject::connect(frame, &Frame::confirmUserDeletion, pController, &ProfileController::confirmUserDeletion);
    QObject::connect(pController, &ProfileController::registrationFailed, frame, &Frame::handleRegistrationFailure);
    QObject::connect(pController, &ProfileController::registrationSucceeded, frame, &Frame::handleRegistrationSuccess);

    // frame <-> gController
    QObject::connect(frame, &Frame::registerDifficulty, gController, &GameController::handleDifficulty);
    QObject::connect(frame, &Frame::registerTileClicked, gController, &GameController::handleTileClicked);
    QObject::connect(frame, &Frame::registerFinishGame, gController, &GameController::handleFinishGame);
    QObject::connect(frame, &Frame::clearGrid, gController, &GameController::handleClearGrid);
    QObject::connect(frame, &Frame::resumeGameTimer, gController, &GameController::resumeTimer);
    QObject::connect(frame, &Frame::registerScore, gController, &GameController::registerScore);
    QObject::connect(frame, &Frame::createLevelEditor, gController, static_cast<void (GameController::*)(Flag)>(&GameController::createLevelEditor));
    QObject::connect(frame, &Frame::updateEditorFlag, gController, &GameController::handleUpdateFlag);
    QObject::connect(frame, &Frame::publishLevel, gController, &GameController::handlePublishLevel);
    QObject::connect(gController, &GameController::levelCreated, frame, &Frame::handleLevelCreated);
    QObject::connect(gController, &GameController::levelChecked, frame, &Frame::handleLevelChecked);
    QObject::connect(gController, &GameController::levelEditorCreated, frame, &Frame::handleLevelEditorCreated);

    // gController <-> pController
    QObject::connect(gController, &GameController::getCurrentUser, pController, &ProfileController::getCurrentUser);
    QObject::connect(pController, &ProfileController::returnCurrentUser, gController, &GameController::handleReturnUser);

    frame->showMainMenu();
    frame->show();

    return a.exec();
}

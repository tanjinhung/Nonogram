#include "frame.h"
#include "profilecontroller.h"

#include <QApplication>

Frame *frame;
ProfileController *pController;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    frame = new Frame();
    pController = new ProfileController();

    QObject::connect(frame, &Frame::registerUser, pController, &ProfileController::registerUser);
    QObject::connect(pController, &ProfileController::registrationFailed, frame, &Frame::handleRegistrationFailure);
    QObject::connect(pController, &ProfileController::registrationSucceeded, frame, &Frame::handleRegistrationSuccess);


    frame->showMainMenu();
    frame->show();

    return a.exec();
}

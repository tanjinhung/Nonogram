#include "frame.h"

#include <QApplication>

Frame* frame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    frame = new Frame();
    frame->show();
    frame->showMainMenu();

    return a.exec();
}

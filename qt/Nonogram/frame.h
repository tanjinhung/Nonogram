#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Frame : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);

    void showMainMenu();
    /*
    void showProfileSelectionScreen();
    void showProfileCreationOverlay();
    void showConfirmationOverlay();
    void showDifficultySelectionScreen();
    */

    QGraphicsScene* scene;


signals:
};

#endif // FRAME_H

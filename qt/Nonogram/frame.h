#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>

class Frame : public QGraphicsView
{
    Q_OBJECT
public:
    Frame(QWidget *parent = nullptr);

    void showMainMenu();
    void showProfileSelectionScreen();
    // void showLevelEditorScreen();
    void showProfileCreationOverlay();
    void showConfirmationOverlay();

    QGraphicsScene* scene;

signals:
    void registerUser(const QString &name, int imageNumber);

public slots:
    void handleRegistrationFailure(const QString &message);
    void handleRegistrationSuccess();

private slots:
    void selectUser(int userId);
    void deleteUser(int userId);
    void destroyProfileOverlay();
    void destroyConfirmationOverlay();
    void destroyOverlay();
    void updateHeroImage(const QString &imagePath);


private:
    QList<QGraphicsItem*> currentItems;
    QList<QWidget*> currentWidgets;
    QLabel *heroImageLabel;
    QGraphicsView *overlayProfileView;
    QGraphicsView *overlayConfirmationView;
    QLineEdit *nameInput;

    int wbWidth = 1000;
    int wbHeight = 600;
    int wbxPos = this->width() / 2 - wbWidth / 2;
    int wbyPos = this->width() / 2 - wbHeight / 2;
    int selectedImageNumber = 1;

    void hideCurrentItems();
};

#endif // FRAME_H

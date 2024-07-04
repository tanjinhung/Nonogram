#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel(parent) {}

void ClickableLabel::setImagePath(const QString &path) {
    imagePath = path;
}

QString ClickableLabel::getImagePath() const {
    return imagePath;
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked(imagePath);
    }
}

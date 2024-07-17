#include "customtile.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>

CustomTile::CustomTile(int row, int col, QGraphicsWidget *parent)
    : QGraphicsWidget(parent), color(Qt::white), row(row), col(col)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CustomTile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit leftButtonClicked();
    } else if (event->button() == Qt::MiddleButton) {
        emit middleButtonClicked();
    } else if (event->button() == Qt::RightButton) {
        emit rightButtonClicked();
    }
}

void CustomTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(color);
    painter->drawRect(rect());

    if (drawXMark) {
        painter->setPen(QPen(Qt::black, 2));
        QLineF lines[2] = {
            QLineF(rect().topLeft(), rect().bottomRight()),
            QLineF(rect().topRight(), rect().bottomLeft())
        };
        painter->drawLines(lines, 2);
    }
}

int CustomTile::getCol() const
{
    return col;
}

int CustomTile::getRow() const
{
    return row;
}

void CustomTile::setColor(const QColor &newColor)
{
    drawXMark = false;
    color = newColor;
    update();
}

void CustomTile::drawX()
{
    drawXMark = true;
    color = Qt::white;
    update();
}


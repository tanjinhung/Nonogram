#ifndef CUSTOMTILE_H
#define CUSTOMTILE_H

#include <QGraphicsWidget>
#include <QColor>
#include <QMouseEvent>

class CustomTile : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit CustomTile(int row, int col, QGraphicsWidget *parent = nullptr);

    void setColor(const QColor &newColor);
    void drawX();

    int getRow() const;
    int getCol() const;

signals:
    void leftButtonClicked();
    void middleButtonClicked();
    void rightButtonClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QColor color;
    int row;
    int col;
    bool drawXMark = false;
};

#endif // CUSTOMTILE_H

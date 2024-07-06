#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QWheelEvent>

class CustomScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    CustomScrollArea(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // CUSTOMSCROLLAREA_H

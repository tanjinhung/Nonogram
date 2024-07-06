#include "CustomScrollArea.h"
#include <QScrollBar>

CustomScrollArea::CustomScrollArea(QWidget *parent)
    : QScrollArea(parent)
{
}

void CustomScrollArea::wheelEvent(QWheelEvent *event)
{
    // Scroll horizontally when the mouse wheel is used
    if (event->angleDelta().y() != 0)
    {
        int numSteps = event->angleDelta().y() / 120; // Each step is 15 degrees, 120/8
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - numSteps * horizontalScrollBar()->singleStep());
        event->accept();
    }
    else
    {
        QScrollArea::wheelEvent(event);
    }
}

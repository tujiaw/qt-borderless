#include "HoverMoveFilter.h"
#include "MainFrame.h"

#include <QEvent>
#include <QHoverEvent>

HoverMoveFilter::HoverMoveFilter(QObject *parent) :
    QObject(parent)
{
}

bool HoverMoveFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *mouseHoverEvent = static_cast<QHoverEvent *>(event);
        MainFrame* frame = static_cast<MainFrame *>(obj);
        frame->mouseMove(mouseHoverEvent->pos(), mouseHoverEvent->oldPos());
    }
    return QObject::eventFilter(obj, event);
}

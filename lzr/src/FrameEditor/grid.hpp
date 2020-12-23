
#pragma once

#include <QtWidgets>
#include <QDebug>
#include "frameeditorstate.hpp"


class Grid : public QGraphicsRectItem
{
public:
    Grid(FrameEditorState* s);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget);

private:
    FrameEditorState* state;
};

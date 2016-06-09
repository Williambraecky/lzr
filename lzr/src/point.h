
#pragma once

#include <QtWidgets>
#include <QDebug>
#include "liblzr.h"



class Point : public QGraphicsItem
{
public:
    Point(lzr::Point);
    ~Point();

    QRectF boundingRect() const;
    void setColor(int r, int g, int b, int a);
    QColor getColor() const;
    lzr::Point to_LZR() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    QColor color;
    bool hovered;
};

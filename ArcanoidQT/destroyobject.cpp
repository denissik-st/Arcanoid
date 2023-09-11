#include "destroyobject.h"
#include <QGradient>
#include <QPen>
#include <QPainter>
#include<qrandom.h>


DestroyObject::DestroyObject()
{
    sizeDestroyObjectX = RandonSizeX();
    sizeDestroyObjectY = 20;
}

QRectF DestroyObject::boundingRect() const
{
    return QRectF(0,0,sizeDestroyObjectX,sizeDestroyObjectY);
}

void DestroyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QLinearGradient *gradient=new QLinearGradient(0,0,0,sizeDestroyObjectY);
    gradient->setColorAt(0, QColor(255,0,255));
    gradient->setColorAt(1, QColor(0,191,255));
    QPen *pen =new QPen;
    pen->setBrush(*gradient);
    painter->setPen(*pen);
    QBrush *brush = new QBrush(*gradient);
    painter->setBrush(*brush);
    painter->drawRect(0,0,sizeDestroyObjectX,sizeDestroyObjectY);

}

int DestroyObject::RandonSizeX()
{

    return (qrand() % ((8 + 1) - 4) + 4)*15;
}

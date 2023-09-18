#include "expansionboardbonus.h"
#include<QPainter>

ExpansionBoardBonus::ExpansionBoardBonus()
{
    //setTransform(QTransform().scale(1.5,1.5));
}

QRectF ExpansionBoardBonus::boundingRect() const
{
    return QRectF(0,0,40,20);
}

void ExpansionBoardBonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen *pen = new QPen;
    pen->setWidth(3);
    pen->setBrush(Qt::white);
    painter->setPen(*pen);
    painter->drawRect(0,0,40,20);
    pen->setWidth(1);
    pen->setColor(Qt::green);
    painter->setPen(*pen);
    QPolygon *polyArrow = new QPolygon;
    polyArrow->append(QPoint(5,10));
    polyArrow->append(QPoint(10,15));
    polyArrow->append(QPoint(10,11));
    polyArrow->append(QPoint(30,11));
    polyArrow->append(QPoint(30,15));
    polyArrow->append(QPoint(35,10));
    polyArrow->append(QPoint(30,5));
    polyArrow->append(QPoint(30,8));
    polyArrow->append(QPoint(10,8));
    polyArrow->append(QPoint(10,4));
    painter->setBrush(QBrush(Qt::green));
    painter->drawPolygon(*polyArrow);

}

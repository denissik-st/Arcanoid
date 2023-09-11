#include "board.h"
#include<QPen>
#include<QPainter>
#include<QDebug>



Board::Board()
{
    boardMatrix = new QTransform;
    speed =20;
    boardSizeX =130;
    boardSizeY =15;

}

QRectF Board::boundingRect() const
{
    return QRectF(0,0,boardSizeX+1,boardSizeY+1);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::white));
    painter->drawRoundedRect(0,0,boardSizeX,boardSizeY,8,8);


}


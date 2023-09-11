#include "ball.h"
#include<QPainter>

Ball::Ball()
{
    start=false;
    speed = 10;
    ballSize =19;
    ballMatrix = new QTransform;

}

QRectF Ball::boundingRect() const
{
    return QRectF(0,0,ballSize+1,ballSize+1);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::white));
    painter->drawEllipse(0,0,ballSize,ballSize);
}

void Ball::moveLeft()
{
    moveBy(-speed,0);
}

void Ball::moveRight()
{
    moveBy(speed,0);
}

void Ball::moveDown()
{
    moveBy(0,speed);
}

void Ball::moveUp()
{
    moveBy(0,-speed);
}

void Ball::setFlagUp()
{
    flagGoUp = true;
}






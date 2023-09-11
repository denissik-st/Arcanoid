#include "ball.h"
#include<QPainter>
#include<QDebug>

Ball::Ball()
{
    start=false;
    speed = 10;
    ballSize =19;
    alpha =M_PI_2;
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


void Ball::moveX(float alpha)
{
    moveBy(speed*qCos(alpha),0);
}

void Ball::moveDown()
{
    moveBy(0,speed);
}

void Ball::moveUp()
{
    moveBy(0,-speed);
}







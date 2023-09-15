#include "live.h"
#include<QPainter>
#include<QtMath>


Live::Live()
{
    setTransform(QTransform().rotate(180));
}

QRectF Live::boundingRect() const
{
    return QRectF(-5,-5,20,20);
}

void Live::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(Qt::red));
    painter->setBrush(QBrush(Qt::red));
    QPolygonF *heart = new QPolygonF;
    for(float i=0;i<2*M_PI;i+=2*M_PI/100){
        QPointF p(6*qCos(i),(6*(qSin(i)+qSqrt(qAbs(qCos(i))))));
        heart->append(p);
    }
    painter->drawPolygon(*heart);

}

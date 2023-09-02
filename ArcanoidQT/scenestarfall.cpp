#include "scenestarfall.h"
#include <QPoint>
#include <QGraphicsPolygonItem>

SceneStarfall::SceneStarfall()
{
    QGraphicsPolygonItem *star1 = new QGraphicsPolygonItem;
    star1->setPolygon(addStar());
    star1->rotation();
    addItem(star1);
}

QPolygon SceneStarfall::addStar()
{
    QPolygon *star = new QPolygon;
    star->append(QPoint(0,30));
    star->append(QPoint(10,15));
    star->append(QPoint(30,10));
    star->append(QPoint(10,5));
    star->append(QPoint(20,-10));
    star->append(QPoint(0,0));
    star->append(QPoint(-20,-10));
    star->append(QPoint(-10,5));
    star->append(QPoint(-30,10));
    star->append(QPoint(-10,15));
    star->append(QPoint(0,30));
    return *star;
}



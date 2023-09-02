#ifndef STAR_H
#define STAR_H
#include<QObject>
#include<QGraphicsPolygonItem>
#include<QTransform>
#include<QGraphicsItem>

//Класс создания "Звезд"
class star : public QObject,QGraphicsPolygonItem
{
    Q_OBJECT
public:
    QTransform *starMatrix;
    QGraphicsPolygonItem *newstar;
    star();
    QPolygon paintStar();
    void rotateStar();
    void setStarX(int x);
    void setStarY(int y);
    void downStarRight();
    void downStarLegt();

};

#endif // STAR_H

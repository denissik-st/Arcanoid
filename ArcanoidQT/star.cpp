#include "star.h"
#include<QPen>

//Конструктор класса "Звезда" с установкой начальных параметров
star::star()
{
    starMatrix = new QTransform;
    newstar = new QGraphicsPolygonItem;
    newstar->setPolygon(paintStar());
    newstar->setPen(QPen(Qt::white));
    newstar->setBrush(QBrush(Qt::white));
    starMatrix->scale(-0.5,-0.5);
    newstar->setTransform(*starMatrix);

}

// Отрисовка "Звезды" по точкам
QPolygon star::paintStar()
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

// Функция вращения звезды
void star::rotateStar()
{
    starMatrix->rotate(12);
    newstar->setTransform(*starMatrix);
}

//Функция установки координаты Х
void star::setStarX(int x)
{
    newstar->setX(x);
}

//Функция установки координаты Y
void star::setStarY(int y)
{
    newstar->setY(y);
}

//Функция "падения звезд вправо и вниз"
void star::downStarRight()
{

    newstar->moveBy(10,10);
    if(newstar->pos().x()>512 || newstar->pos().y()>384){
        newstar->setX(rand()%512-512);
        newstar->setY(rand()%1024-1024);
    }

}

//Функция "падения звезд влево и вниз"
void star::downStarLegt()
{
    newstar->moveBy(-10,10);
    if(newstar->pos().x()<-512 || newstar->pos().y()<-384){
        newstar->setX(rand()%1024);
        newstar->setY(rand()%384-384);
    }
}





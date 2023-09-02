#ifndef SCENESTARFALL_H
#define SCENESTARFALL_H
#include<QGraphicsScene>
#include<QGraphicsPolygonItem>
#include "star.h"

// Класс сцены падающих звезд (задний фон начального меню)
class SceneStarfall : public QGraphicsScene
{
    Q_OBJECT
public:
    QTimer *timerStarfall;
    star *massivStar;
    int countStar =20;
    SceneStarfall();
public slots:
    void rotateAndDownStar();

};

#endif // SCENESTARFALL_H

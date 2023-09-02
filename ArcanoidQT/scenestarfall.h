#ifndef SCENESTARFALL_H
#define SCENESTARFALL_H
#include<QGraphicsScene>


class SceneStarfall : public QGraphicsScene
{
    Q_OBJECT
public:
    SceneStarfall();
    QPolygon addStar();
};

#endif // SCENESTARFALL_H

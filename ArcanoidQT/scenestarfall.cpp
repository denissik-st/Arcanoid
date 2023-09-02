#include "scenestarfall.h"
#include<QGraphicsPolygonItem>
#include<QTimer>
#include<random>

//Конструктор класс, содержит массив из "Звезд" и таймер для регулировки падения.
SceneStarfall::SceneStarfall()
{   
    massivStar = new star[countStar];
    timerStarfall = new QTimer;
    srand(10);
    timerStarfall->setInterval(50);
    connect(timerStarfall,SIGNAL(timeout()),this,SLOT(rotateAndDownStar()));
    int startStarX=rand()%512-512;
    for(int i=0;i<countStar;i++){
        int startStarY=rand()%1024-1024;
        massivStar[i].setStarX(startStarX);
        massivStar[i].setStarY(startStarY);
        addItem(massivStar[i].newstar);
        startStarX=rand()%512-512;


    }
    timerStarfall->start();

}

void SceneStarfall::rotateAndDownStar()
{
    for(int i=0;i<countStar/2;i++){
        massivStar[i].rotateStar();
        massivStar[i].downStarRight();
    }
    for(int i=countStar/2;i<countStar;i++){
        massivStar[i].rotateStar();
        massivStar[i].downStarLegt();
    }
}






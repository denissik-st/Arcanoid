#include "sceneplaygame.h"
#include <QTimer>
#include <QDebug>
#include<QList>
#include<QTransform>
#include<QPushButton>
scenePlayGame::scenePlayGame()
{
    //Панель состояния
    scenePlayGameWight = 996;
    scenePlayGameHeight = 730;
    addLine(0,20,1000,20,QPen(Qt::white));
    addLine(0,20,2,768,QPen(Qt::white));
    addLine(1000,20,1000,768,QPen(Qt::white));
    QLabel *namePointGame = new QLabel;
    namePointGame->setText("Ваш счет:");
    namePointGame->setGeometry(900,0,50,15);
    namePointGame->setStyleSheet("background-color: rgba(0,0,0,10);color: white;");
    addWidget(namePointGame);
    pointGamelbl = new QLabel;
    pointGamelbl->setGeometry(950,0,50,15);
    pointGamelbl->setStyleSheet("background-color: rgba(0,0,0,10);color: white;");
    pointGamelbl->setAlignment(Qt::AlignRight);
    pointGamelbl->setText("0");
    addWidget(pointGamelbl);
    //Кнопка отладки
    /*QPushButton *deleteDestroyObjbtn = new QPushButton;
    deleteDestroyObjbtn->setText("Удалить");
    addWidget(deleteDestroyObjbtn);*/
    //Создание доски
    playBoard = new Board;
    playBoard->setX(512-playBoard->boardSizeX/2);
    playBoard->setY(730);
    addItem(playBoard);
    //Создание мяча
    playBall =new Ball;
    playBall->setX(512-20/2);
    playBall->setY(710);
    playBall->flagGoUp=true;
    playBall->flagGoLeft=false;
    addItem(playBall);
    //Создание разрушаемых объектов
    listDestroyObject =new QList <QGraphicsItem *>;
    int destoyObjectY =23;
    for (int j=destoyObjectY;j<scenePlayGameHeight/3;) {
        int destroyObjectX =3;
        for(int i = destroyObjectX;i<scenePlayGameWight;){
            destoyObject = new DestroyObject;
            if(destroyObjectX+destoyObject->sizeDestroyObjectX>scenePlayGameWight){ //Ограничение выхода объектов за пределы экрана
                destoyObject->sizeDestroyObjectX = scenePlayGameWight - destroyObjectX-1;
            }
            listDestroyObject->append(destoyObject);
            destoyObject->setX(destroyObjectX);
            destoyObject->setY(destoyObjectY);
            i+=destoyObject->sizeDestroyObjectX+4;
            destroyObjectX+=destoyObject->sizeDestroyObjectX+4;
            addItem(destoyObject);
        }
        destoyObjectY+=destoyObject->sizeDestroyObjectY+4;
        j+=destoyObject->sizeDestroyObjectY+4;

    }

    //Таймер для запуска игры
    playTimer = new QTimer;
    playTimer->setInterval(45);
    connect(playTimer,SIGNAL(timeout()),this,SLOT(moveBall()));
    //connect(deleteDestroyObjbtn,SIGNAL(clicked()),this,SLOT(deleteAllDectroyObject())); коннект для отладочной кнопки

}

//Обратока клавиатуры
void scenePlayGame::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        if(playBoard->pos().x()>8){
            playBoard->moveBy(-playBoard->speed,0);
        }
        if(!playBall->start&&playBall->pos().x()>2+playBoard->boardSizeX/2-playBall->ballSize){
            playBall->moveBy(-playBoard->speed,0);
        }
    }
    if(event->key()==Qt::Key_Right){
        if(playBoard->pos().x()<867){
            playBoard->moveBy(playBoard->speed,0);
        }
        if(!playBall->start&&playBall->pos().x()<867+playBoard->boardSizeX/2-playBall->ballSize){
            playBall->moveBy(playBoard->speed,0);
        }
    }
    if(event->key()==Qt::Key_Space){
        playBall->start=true;
        playTimer->start();
    }
}

//Движение мяча
void scenePlayGame::moveBall()
{
    if(playBall->flagGoUp && playBall->flagGoLeft){
        playBall->moveUp();
        playBall->moveLeft();

    }
    if(!playBall->flagGoUp && playBall->flagGoLeft){
        playBall->moveDown();
        playBall->moveLeft();
    }
    if(playBall->flagGoUp && !playBall->flagGoLeft){
        playBall->moveUp();
        playBall->moveRight();
    }
    if(!playBall->flagGoUp && !playBall->flagGoLeft){
        playBall->moveDown();
        playBall->moveRight();
    }
    if(playBall->pos().x()<20){
        playBall->flagGoLeft=false;
    }
    if(playBall->pos().x()>1000-playBall->ballSize){
        playBall->flagGoLeft=true;
    }
    if(playBall->pos().y()<20+playBall->ballSize/2){
        playBall->flagGoUp=false;
    }
    if(playBall->pos().y()>768+playBall->ballSize/2){
        playTimer->stop();
        emit endGame(pointGamelbl->text().toInt());
    }
    //Обработка событий "коллизий" доски (встреча объектов с доской)
    if(!collidingItems(playBoard).isEmpty()){
        QList <QGraphicsItem *> *boardList = new QList<QGraphicsItem *>;
        *boardList = collidingItems(playBoard);
        for(QGraphicsItem *item:*boardList){
            if(item==playBall){
                playBall->flagGoUp=true;
               if(item->pos().x()-playBoard->pos().x()+playBall->ballSize/2<playBoard->boardSizeX/2){
                   playBall->flagGoLeft = true;
               }
               else {
                   playBall->flagGoLeft = false;
               }
            }
        }
    }
    // Обработка событий "коллизий" мяча
    if(!collidingItems(playBall).isEmpty()){
        QList <QGraphicsItem *> *ballList = new QList<QGraphicsItem *>;
        *ballList = collidingItems(playBall);
        for(QGraphicsItem *itemBall:*ballList){
            int count=0;
            for(QGraphicsItem *itemDestoyObjectList:*listDestroyObject){
                if(itemBall==itemDestoyObjectList){
                    if(itemBall->pos().y()+destoyObject->sizeDestroyObjectY/2<playBall->pos().y()){ // если встреча произошла до середины разрушаемого объекта
                        playBall->flagGoUp=false;
                    }
                    else {
                        playBall->flagGoUp=true;
                    }
                    //Запись очков
                    int *plusGamePoint = new int;
                    *plusGamePoint = itemDestoyObjectList->boundingRect().size().width();
                    int *nowGamePoint = new int;
                    *nowGamePoint = pointGamelbl->text().toInt();
                    *nowGamePoint+=*plusGamePoint;
                    pointGamelbl->setText(QString::number(*nowGamePoint));
                    //Удаление разрушаемых объектов
                    removeItem(itemDestoyObjectList);
                    listDestroyObject->removeAt(count);
                }
                count++;
            }
        }
    }
    if(listDestroyObject->isEmpty()){
        playTimer->stop();
        emit endGame(pointGamelbl->text().toInt());
    }
}
// Сигнал для отладки (Удаляется все разрущаемые объекты)
/*void scenePlayGame::deleteAllDectroyObject()
{
    QList <QGraphicsItem *> *itemScene = new QList <QGraphicsItem *>;
    *itemScene =this->items();
    for(QGraphicsItem *item:*itemScene){
        for(QGraphicsItem *itemDest:*listDestroyObject){
            if(item == itemDest){
                removeItem(item);
            }
        }
    }
    listDestroyObject->clear();
}*/

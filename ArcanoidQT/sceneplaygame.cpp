#include "sceneplaygame.h"
#include <QTimer>
#include <QDebug>
#include<QList>
#include<QTransform>
#include<QPushButton>
#include<qrandom.h>


scenePlayGame::scenePlayGame()
{

    qsrand(time(NULL));
    //Панель состояния
    scenePlayGameWight = 996;
    scenePlayGameHeight = 730;
    //Отрисовка левой границы
    leftLine = new QLine;
    leftLine->setLine(0,20,2,768);
    addLine(*leftLine,QPen(Qt::white));
    //Отрисовка правой границы
    rightline = new QLine;
    rightline->setLine(1000,20,1000,768);
    addLine(*rightline,QPen(Qt::white));
    //Отрисовка верхней границы
    addLine(0,20,1000,20,QPen(Qt::white));
    //Виджет "счет игрока"
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
    //Создание босунов
    expansionBoardBonus = NULL; // Приравнивание в NULL необходимо, т.к. пока бонус будет
                                //обрабатываться в общем таймере (будет происходить проверка на существование)
    //Кнопка отладки
    /*QPushButton *deleteDestroyObjbtn = new QPushButton;
    deleteDestroyObjbtn->setText("Удалить");
    addWidget(deleteDestroyObjbtn);*/
    //Создание доски
    playBoard = new Board;
    addItem(playBoard);
    //Создание мяча
    playBall =new Ball;
    setPosBoardAndBall();
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
    //Создание игровых "жизней"
    playLivesList = new QList <QGraphicsItem *>;
    int startLivePosX=15;
    int startLivePosY=10;
    for (int i=0;i<3;i++) { // Начальное количество жизней - 3
        Live *live = new Live;
        playLivesList->append(live);
        live->setPos(startLivePosX,startLivePosY);
        addItem(live);
        startLivePosX+=17;
    }


    //Таймер для запуска игры
    playTimer = new QTimer;
    playTimer->setInterval(45);
    connect(playTimer,SIGNAL(timeout()),this,SLOT(moveBall()));
    //connect(deleteDestroyObjbtn,SIGNAL(clicked()),this,SLOT(deleteAllDectroyObject())); коннект для отладочной кнопки

}

void scenePlayGame::setPosBoardAndBall()
{
    playBoard->setX(512-playBoard->boardSizeX/2);
    playBoard->setY(730);
    playBall->setX(512-20/2);
    playBall->setY(710);
    playBall->flagGoUp=true;
}

//Обратока клавиатуры
void scenePlayGame::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        if(playBoard->pos().x()>8){
            playBoard->moveBy(-playBoard->speed,0);
        }
        if(!playBall->start&&playBall->pos().x()>8+playBoard->boardSizeX/2-playBall->ballSize){
            playBall->moveBy(-playBoard->speed,0);
        }
    }
    if(event->key()==Qt::Key_Right){
        if(playBoard->pos().x()<1000-playBoard->boardSizeX-8){
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

//Игровой таймер (движение мяча и бонусов)
void scenePlayGame::moveBall()
{
    if(playBall->flagGoUp){
        playBall->moveUp();
        playBall->moveX(playBall->alpha);

    }
    if(!playBall->flagGoUp ){
        playBall->moveDown();
        playBall->moveX(playBall->alpha);
    }
    if(playBall->pos().x()>1000-playBall->ballSize){
        playBall->alpha=playBall->alpha+M_PI;
        playBall->setX(1000-playBall->ballSize);
    }
    if(playBall->pos().x()<0){
        playBall->alpha=playBall->alpha-M_PI;
        playBall->setX(0);
    }

    if(playBall->pos().y()<20+playBall->ballSize/2){
        playBall->flagGoUp=false;
    }
    if(playBall->pos().y()>768+playBall->ballSize/2){
        playTimer->stop();
        playBall->start = false;
        playBall->alpha = M_PI_2;
        removeItem(playLivesList->takeLast());
        if(expansionBoardBonus){ // удаление бонуса в случаи проигрыша
            removeItem(expansionBoardBonus);
            expansionBoardBonus =NULL;
        }
        setPosBoardAndBall();
        if(playLivesList->isEmpty()){
            disconnect(playTimer,SIGNAL(timeout()),this,SLOT(moveBall()));
            emit endGame(pointGamelbl->text().toInt());
        }
    }
    //Обработка событий "коллизий" доски (встреча объектов с доской)
    if(!collidingItems(playBoard).isEmpty()){
        QList <QGraphicsItem *> *boardList = new QList<QGraphicsItem *>;
        *boardList = collidingItems(playBoard);
        for(QGraphicsItem *item:*boardList){
            if(item==playBall){
               playBall->flagGoUp=true;
               playBall->alpha=((playBoard->boardSizeX-(playBall->pos().x()-playBoard->pos().x()))-playBall->ballSize/2)*(M_PI/(float)playBoard->boardSizeX);
            }
            if(item==expansionBoardBonus){//удлинение доски
                if(playBoard->boardSizeX<500){
                    playBoard->boardSizeX+=30;
                }
                removeItem(expansionBoardBonus);
                expansionBoardBonus =NULL;
                playBoard->update();
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
                    //Проверка на бонус
                    if(qrand()%100>95){
                        // Условие, что бонус увечивения длины доски не существует
                        if(!expansionBoardBonus){
                            expansionBoardBonus = new ExpansionBoardBonus;
                            expansionBoardBonus->setY(itemDestoyObjectList->pos().y());
                            expansionBoardBonus->setX(itemDestoyObjectList->pos().x()+itemDestoyObjectList->boundingRect().width()/2);
                            addItem(expansionBoardBonus);
                        }
                    }
                    //Удаление разрушаемых объектов
                    removeItem(itemDestoyObjectList);
                    listDestroyObject->removeAt(count);
                }
                count++;
            }
        }
    }
    if(expansionBoardBonus){ // движение бонуса
        expansionBoardBonus->moveBy(0,5);
        if(expansionBoardBonus->pos().y()>768){
            removeItem(expansionBoardBonus);
            expansionBoardBonus =NULL;
        }
    }
    // Все разрушаемые объекты уничтожены
    if(listDestroyObject->isEmpty()){
           playTimer->stop();
           disconnect(playTimer,SIGNAL(timeout()),this,SLOT(moveBall()));
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

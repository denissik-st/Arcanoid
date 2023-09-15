#ifndef SCENEPLAYGAME_H
#define SCENEPLAYGAME_H
#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QLabel>
#include "board.h"
#include "ball.h"
#include "destroyobject.h"
#include "live.h"


class scenePlayGame : public QGraphicsScene
{
    Q_OBJECT
public:
    int scenePlayGameWight;
    int scenePlayGameHeight;
    QLabel *pointGamelbl;
    Board *playBoard;
    Ball *playBall;
    DestroyObject *destoyObject;
    QList <QGraphicsItem *> *listDestroyObject;
    QList <QGraphicsItem *> *playLivesList;
    QTimer *playTimer;
    scenePlayGame();
    void setPosBoardAndBall();
    signals:
    void endGame(int result);
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void moveBall();
    //void deleteAllDectroyObject();

};

#endif // SCENEPLAYGAME_H

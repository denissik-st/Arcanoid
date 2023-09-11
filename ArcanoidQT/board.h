#ifndef BOARD_H
#define BOARD_H
#include<QGraphicsItem>
#include<QTransform>
#include<QGraphicsScene>
#include<QList>


class Board : public QGraphicsItem,QObject
{

public:
    int boardSizeX;
    int boardSizeY;
    int speed;
    QList<QGraphicsItem *> *boardListItem;
    QTransform *boardMatrix;
    Board();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // BOARD_H

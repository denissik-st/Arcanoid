#ifndef BALL_H
#define BALL_H
#include<QGraphicsItem>
#include<QTransform>

class Ball : public QGraphicsItem
{
public:
    bool start;
    int speed;
    int ballSize;
    bool flagGoUp;
    bool flagGoLeft;
    QTransform *ballMatrix;
    Ball();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void setFlagUp();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // BALL_H

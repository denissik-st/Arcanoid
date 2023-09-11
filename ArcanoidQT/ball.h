#ifndef BALL_H
#define BALL_H
#include<QGraphicsItem>
#include<QTransform>
#include <QtMath>

class Ball : public QGraphicsItem
{
public:
    float alpha;
    bool start;
    int speed;
    int ballSize;
    bool flagGoUp;
    QTransform *ballMatrix;
    Ball();
    void moveX(float alpha);
    void moveDown();
    void moveUp();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // BALL_H

#ifndef DESTROYOBJECT_H
#define DESTROYOBJECT_H
#include<QGraphicsItem>


class DestroyObject : public QGraphicsItem // Разрушаемые объекты
{
public:
    int sizeDestroyObjectX;
    int sizeDestroyObjectY;
    DestroyObject();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int RandonSizeX();
};

#endif // DESTROYOBJECT_H

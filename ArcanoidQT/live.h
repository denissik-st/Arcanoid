#ifndef LIVE_H
#define LIVE_H
#include <QGraphicsItem>

class Live : public QGraphicsItem
{
public:
    Live();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // LIVE_H

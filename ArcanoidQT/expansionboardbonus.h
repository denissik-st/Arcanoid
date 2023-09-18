#ifndef EXPANSIONBOARDBONUS_H
#define EXPANSIONBOARDBONUS_H
#include <QGraphicsItem>


class ExpansionBoardBonus : public QGraphicsItem // Бонус увеличения длины доски
{
public:
    ExpansionBoardBonus();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // EXPANSIONBOARDBONUS_H

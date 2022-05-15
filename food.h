#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>

class Food : public QGraphicsItem
{
public:
    Food(qreal x, qreal y,int score,int size);
    int Score();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;

private:
    int score;
    int size;
};

#endif // FOOD_H

#ifndef SNAKENODE_H
#define SNAKENODE_H

#include<QPointF>

#include"constants.h"

class SnakeNode
{
public:
    SnakeNode(QPointF position,Direction direction);
    SnakeNode(const SnakeNode& node);
    bool operator==(const SnakeNode& s);
    void setPos(QPointF pos);
    QPointF pos() const;

    void setDirection(Direction dir);
    Direction getDirection();

    qreal x() const;
    qreal y() const;
    qreal &rx();
    qreal &ry();
    void setX(qreal x);
    void setY(qreal y);

    qreal getX() const;
    qreal getY() const;

private:
    QPointF position;
    Direction direction;
};

#endif // SNAKENODE_H

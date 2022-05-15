#include<QPointF>

#include "snakenode.h"

SnakeNode::SnakeNode(QPointF position, Direction direction):
    position(position),
    direction(direction)
{
}

SnakeNode::SnakeNode(const SnakeNode &node)
{
    position=node.position;
    direction=node.direction;
}

bool SnakeNode::operator==(const SnakeNode &s)
{
    return s.pos()==pos();
}

void SnakeNode::setPos(QPointF pos)
{
    position=pos;
}

QPointF SnakeNode::pos() const
{
    return position;
}

void SnakeNode::setDirection(Direction dir)
{
    direction=dir;
}

Direction SnakeNode::getDirection()
{
    return direction;
}

qreal SnakeNode::x() const
{
    return position.x();
}

qreal SnakeNode::y() const
{
    return position.y();
}

qreal &SnakeNode::rx()
{
    return position.rx();
}

qreal &SnakeNode::ry()
{
    return position.ry();
}

void SnakeNode::setX(qreal x)
{
    position.setX(x);
}

void SnakeNode::setY(qreal y)
{
    position.setY(y);
}

qreal SnakeNode::getX() const
{
    return position.x();
}

qreal SnakeNode::getY() const
{
    return position.y();
}

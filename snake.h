#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

#include"constants.h"
#include"snakenode.h"
#include"skin.h"

class Game;

class Snake : public QGraphicsItem
{
public:

    Snake(Game & controller);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    //修改设置属性
    void setMoveDirection(Direction direction);
    void setSpeed(int speed);

protected:
    void advance(int step);

private:
    //修改方向记录
    void setLastDirection(Direction direction);

    bool ishandle();

    //根据方向前进
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

    Game &game;
    SnakeNode   head;
    QList<SnakeNode> body;
    Skin skin;
    int            growing;
    int            speed;
    int            tick;
    Direction      direction;
    Direction   lastdirection;
};

#endif // SNAKE_H

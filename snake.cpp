#include <QPainter>
#include<QDebug>
#include "constants.h"
#include "Game.h"
#include "snake.h"

Snake::Snake(Game &game) :
    game(game),
    head(QPointF(0, 0),NoDirection),
    skin(10),
    growing(7),
    speed(game.Diffculty()),
    direction(NoDirection),
    lastdirection(NoDirection)
{
}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (SnakeNode p, body) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + tile,      // width
                          br.y() - tl.y() + tile       //height
                          );
    return bound;
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0,0, tile, tile));

    foreach (SnakeNode p, body) {
        QPointF itemp = mapFromScene(p.pos());
        path.addRect(QRectF(itemp.x(), itemp.y(), tile, tile));
    }
    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->fillRect(0,0,tile,tile,skin.getPic(0,head.getDirection()));
    for(int i=0;i<body.size();i++){
        QPointF itemp=mapFromScene(body[i].pos());
        painter->fillRect(int(itemp.x()),int(itemp.y()),tile,tile,skin.getPic(i+1,body[i].getDirection()));
    }
    painter->restore();
}

void Snake::setMoveDirection(Direction dir)
{
    if(direction==Left&&dir==Right) return;
    else if(direction==Right&&dir==Left) return;
    else if(direction==Up&&dir==Down) return;
    else if(direction==Down&&dir==Up) return;
    direction = dir;
}

void Snake::setSpeed(int sp)
{
    speed=sp;
}

void Snake::setLastDirection(Direction dir)
{
    lastdirection=dir;
}

bool Snake::ishandle()
{
    tick++;
    if(tick==tickCount[speed]) {
        tick=0;
        return true;
    }
    else
        return false;
}

void Snake::advance(int step)
{
    //第一次连接
    if (step==0) {
        return;
    }
    else{
        //防止异步干扰
        Direction NowDir=direction;

        //不处理就返回
        if(!ishandle())
            return;

        //无方向就返回
        if (direction == NoDirection) {
            return;
        }

        SnakeNode Lasthead=head;
        head.setDirection(direction);
        //头
        switch (NowDir) {
            case Left:
                moveLeft();
                break;
            case Right:
                moveRight();
                break;
            case Up:
                moveUp();
                break;
            case Down:
                moveDown();
                break;
            case NoDirection:
                break;
        }

        //处理增量
        body.push_front(Lasthead);
        if (growing > 0) {
            growing -= 1;
        } else {
            body.pop_back();
        }
        setPos(head.pos());
        handleCollisions();
    }

}

void Snake::moveLeft()
{
    head.rx() -= tile;
    if (head.rx() < Viewer.topLeft().x()) {
        head.rx() = Viewer.bottomRight().x()-tile;
    }
}

void Snake::moveRight()
{
    head.rx() += tile;
    if (head.rx() >= Viewer.bottomRight().x()) {
        head.rx() = Viewer.topLeft().x();
    }
}

void Snake::moveUp()
{
    head.ry() -= tile;
    if (head.ry() < Viewer.topLeft().y()) {
        head.ry() = Viewer.bottomRight().y()-tile;
    }
}

void Snake::moveDown()
{
    head.ry() += tile;
    if (head.ry() >=Viewer.bottomRight().y()) {
        head.ry() = Viewer.topLeft().y();
    }
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    // Check collisions with other objects on screen
    for (int i=0;i<collisions.size();i++) {
        if (collisions[i]->data(G_Type) == GO_Food) {
            // Let Game handle the event by putting another apple
            game.snakeAteFood(this, (Food *)collisions[i]);
            growing += 1;
        }
    }

    // Check snake eating itself
    if (body.contains(head)) {
        game.snakeAteItself(this);
    }
}

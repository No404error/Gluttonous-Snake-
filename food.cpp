#include <QPainter>

#include "constants.h"
#include "food.h"

static const qreal FOOD_RADIUS = tile/3;

Food::Food(qreal x, qreal y,int score,int size):
    score(score),
    size(size)
{
    setPos(x, y);
    setData(G_Type, GO_Food);
}

int Food::Score()
{
    return size*score;
}

QRectF Food::boundingRect() const
{
    return QRectF(0,    0,
                   tile *size, tile * size );
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), Qt::red);

    painter->restore();
}

QPainterPath Food::shape() const
{
    QPainterPath p;
    p.addEllipse(QPointF(tile*size / 2, tile*size / 2), FOOD_RADIUS, FOOD_RADIUS);
    return p;
}

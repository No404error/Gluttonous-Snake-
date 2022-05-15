#ifndef TEXT_H
#define TEXT_H

#include <QGraphicsTextItem>

class Text : public QGraphicsSimpleTextItem
{
public:
    Text(QPointF pos,bool run,int score,int diffculty);
};

#endif // TEXT_H

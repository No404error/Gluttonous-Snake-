#include<QColor>
#include<QBrush>
#include<QFont>
#include<QString>
#include<QPainter>

#include"constants.h"
#include "text.h"


Text::Text(QPointF pos,bool run,int score,int diffculty)
{
    setPos(pos);
    setData(G_Type,GO_Text);
    setBrush(Qt::yellow);
    QString str;
    if(run)
        str="Score："+QString::number(score)+"\nLevel: "+QString::number(diffculty);
    else
        str="Pause";
    setText(str);
    setFont(QFont("Consolas",6));
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
}

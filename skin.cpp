#include<QRandomGenerator>
#include<QTime>
#include<QPainter>

#include "skin.h"

QColor getRandomColor(QRandomGenerator &rand)
{
    std::uniform_int_distribution<int> format(10,245);
    int r=format(rand);
    int g=format(rand);
    int b=format(rand);
    QColor color=QColor(r,g,b);
    return color.lighter();
}

QColor *getRandomColors(QRandomGenerator &rand, int len)
{
    QColor *colors=new QColor[uint(len)];
    for(int i=0;i<len;i++)
        colors[i]=getRandomColor(rand);
    return colors;
}

Skin::Skin():
    rand(uint(QTime(0,0,0).secsTo(QTime::currentTime())))
{
    QColor color=getRandomColor(rand);
    QPixmap p(tile,tile);
    //获得头
    p.fill(color);
    setHeadPic(p);
    addPic(p);
    //获得躯干
    p.fill(color);
    addPic(p);
}

Skin::Skin(int len):
    rand(uint(QTime(0,0,0).secsTo(QTime::currentTime())))
{
    QColor *colors=getRandomColors(rand,len);
    QPixmap p(tile,tile);
    for(int i=0;i<len;i++){
        p.fill(colors[i]);
        addPic(p);
    }
    setHeadPic(skinp[0]);
}

Skin::Skin(const Skin &skin)
{
    skinp.append(skin.skinp);
    rand=skin.rand;
}

void Skin::addPic(QPixmap pic)
{
    skinp.push_back(pic);
}

QPixmap Skin::getPic(int pos, Direction dir)
{
    //获得有效索引
    if(pos>0) pos=pos%(skinp.size()-1)+1;
    QMatrix format;
    if(dir==Left)
        format.rotate(90);
    else if(dir==Up)
        format.rotate(180);
    else if(dir==Right)
        format.rotate(270);
    return skinp[pos].transformed(format, Qt::SmoothTransformation);
}

void Skin::setHeadPic(QPixmap &pic)
{
    QPainter painter(&pic);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);
    double radio=(1-SnakeEyeOfHead)/2;
    int eye1x=(int)(radio*tile);
    int eye2x=(int)((radio+SnakeEyeOfHead)*tile);
    painter.drawEllipse(eye1x,3*tile/4,tile/20,tile/10);
    painter.drawEllipse(eye2x,3*tile/4,tile/20,tile/10);
}

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include<QRectF>

//格子大小
const int tile = 10;
//场景大小
const QRectF Viewer=QRectF(-100,-100,200,200);
//文本栏的位置
const QPointF Textpos=QPointF(Viewer.topLeft().x()+Viewer.width()*9/13,Viewer.topLeft().y()+Viewer.height()/50);
//游戏引擎刷新率
const int Ehz=66;
//游戏结束暂停时间(ms)
const int GameOverTime=1000;
//游戏难度上限
const int DiffcultyTop=4;
//游戏初始难度
const int init_diffculty=3;

//蛇的皮肤长度
const int init_skin_size=15;
//蛇的初始长度
const int init_size=6;
//蛇眼睛占头的比例
const double SnakeEyeOfHead=0.4;
//难度对应的蛇的响应时间
const int BaseTick=Ehz/5;
const int tickCount[]={0,BaseTick,BaseTick/2,BaseTick/3,BaseTick/4,BaseTick/5};
//难度对应的分数
const int diffculty_value[]={1,2,3,4,5};

enum Direction{
    Left,
    Right,
    Up,
    Down,
    NoDirection
};

enum GameObjectsData {
    G_Type
};

enum GameObjectTypes {
    GO_Text,
    GO_Food,
    GO_Wall,
    GO_Node
};

#endif // CONSTANTS_H

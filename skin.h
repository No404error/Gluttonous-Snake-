#ifndef SKIN_H
#define SKIN_H

#include<QVector>
#include<QPixmap>
#include<QRandomGenerator>

#include"constants.h"

class Skin
{
public:
    Skin();
    Skin(int len);
    Skin(const Skin& skin);

    void addPic(QPixmap pic);
    QPixmap getPic(int pos,Direction dir);
private:
   void setHeadPic(QPixmap& pic);

   QVector<QPixmap> skinp;
   QRandomGenerator rand;
};
QColor getRandomColor(QRandomGenerator& rand);
QColor *getRandomColors(QRandomGenerator& rand, int len);

#endif // SKIN_H

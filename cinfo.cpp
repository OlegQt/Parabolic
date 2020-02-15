#include "cinfo.h"

CInfo::CInfo()
{

    this->inforLayer = QPixmap(300,50);
    this->strInfo="First line";
    this->paintInfo(); //Первичная отрисовка



}

void CInfo::paintInfo()
{
    QPainter * painter = new QPainter();
    this->inforLayer.fill(QColor(0, 0, 0, 50));
    QPen * fontPen = new QPen(QColor("white"));
    // Ниже начинаем отрисовку информационного буфера в QPixmap
    painter->begin(&this->inforLayer);
    painter->setPen(*fontPen);
    painter->drawText(0,16,this->strInfo);
    painter->drawText(0,40,"Information");
    painter->end();
    delete  painter;
}

void CInfo::setInfo(int type, QString str, int a)
{
    switch (type) {
    case 0:
        this->strInfo=str+QString::number(a);
        this->paintInfo();
        break;
    }
}

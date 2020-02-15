#ifndef CINFO_H
#define CINFO_H
#include "QPixmap"
#include "QPainter"

class CInfo
{
public:
    CInfo();
    void paintInfo();
    QPixmap info(){return this->inforLayer;}
    void setInfo(int type, QString str, int a);
private:
    QPixmap inforLayer;
    QString strInfo;
};

#endif // CINFO_H

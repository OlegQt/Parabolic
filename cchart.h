#ifndef CCHART_H
#define CCHART_H

#include <QObject>
#include <QQuickItem>
#include "QPainter"
#include "QPainterPath"
#include "QtMath"


class CChart
{
    //Q_OBJECT
public:
    CChart(unsigned int functionType);
    CChart(unsigned int type,qreal factorA,qreal factorB, qreal factorC);

    void getFromPoints(QPointF pointA,QPointF pointB);
    qreal getY(qreal X);
    void paint(QPainter*painter);
private:
    unsigned int type; // Тип функции
    qreal factorA,factorB,factorC; // Коэффициенты функции в зависимости от типа
    QPainterPath * chartPath;

signals:

};

#endif // CCHART_H

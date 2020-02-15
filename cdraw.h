#ifndef CDRAW_H
#define CDRAW_H
#include "QQuickPaintedItem"
#include "QPainter"
#include "QPainterPath"
#include "QtDebug"
#include "cchart.h"
#include "QVector"
#include "QtMath"
#include "cinfo.h"


class CDraw: public QQuickPaintedItem
{
    Q_OBJECT
public:
    CDraw();
    ~CDraw();
public:
    void paint(QPainter * painter);

    Q_INVOKABLE QString getMousePos();
    Q_INVOKABLE QString getDebugInfo();

    Q_INVOKABLE void onMouseMove(qreal xpos,qreal ypos);
    Q_INVOKABLE void setDelta(qreal xpos,qreal ypos);
    Q_INVOKABLE qreal getRealY(qreal fakeY);
    Q_INVOKABLE void  onMouseClick(qreal xpos,qreal ypos);
    Q_INVOKABLE void cleareAllCharts();
    Q_INVOKABLE QString getFtype();
    Q_INVOKABLE void setFtype(unsigned int type);
private:
    QString getPointstr(const QString str,QPointF point);
    int createChart(unsigned int type);
    void translatePointToVirtual(qreal * x,qreal *y);
    void paintBuffer();
    void paintTemporalChart(CChart * temporalChart);
private:
    QPainterPath * fullLine, * temporalLine; // Массив точек на отрисовку
    QPointF * mousePos; // Расположение курсора
    QPointF * delta; // Смещение виртуального экрана
    QPointF pointA, pointB; // Две точки
    bool onClicked;
    unsigned int currentFunctionType;
    QString strDebug;
    QPixmap bufferImg; // Графический буфер
    QVector<CChart *> chartVector; // Вектор из графиков
    CInfo * inforLayer;

signals:
};

#endif // CDRAW_H

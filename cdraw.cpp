#include "cdraw.h"

CDraw::CDraw()
{
    this->mousePos = new QPointF(5,5);
    this->fullLine=new QPainterPath();
    this->temporalLine=new QPainterPath();
    this->delta=new QPointF(0,0);
    this->onClicked=false; // true если произведено нечетное нажатие
    this->currentFunctionType=0;

    this->inforLayer = new CInfo();
    inforLayer->setInfo(0,"Hellow ",11);

    this->bufferImg = QPixmap(100,100);

}
CDraw::~CDraw()
{
    qDebug()<<"DrawDestructor";
    this->fullLine->clear();
    this->pointA.~QPointF();
    this->pointB.~QPointF();
    this->cleareAllCharts(); // Удаление вектора графиков
    this->chartVector.clear();
    this->fullLine->clear();
    this->temporalLine->clear();
    delete this->fullLine;
    delete this->temporalLine;
    delete this->mousePos;
    delete this->delta;
    //this->bufferImg.~QPixmap();

}

void CDraw::paint(QPainter *painter)
{
    QPen * pen = new QPen(Qt::SolidLine);
    pen->setWidth(2);
    pen->setColor(QColor("red"));
    painter->setPen(*pen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawPixmap(0,0,this->bufferImg);

    //painter->translate(*this->delta); // Смещение виртуального окна
    painter->drawPath(*this->fullLine); // Отрисовка графика
    painter->drawPath(*this->temporalLine); // Отрисовка графика

    // Размещаем буфер с информацией по нижней границе render target
    painter->drawPixmap(0,this->height()-this->inforLayer->info().height(),this->inforLayer->info());
    // painter->drawEllipse(this->width()-this->delta->x(),this->getRealY(20),5,5);
    // Смещение задается глобальной переменной delta(X,Y)
    // Системная инверсия оси Y
    // При любом смещении координаты виртуального окна
    // left = - delta->x()
    // right = width()-delta->x()
    // top = getRealY(height()) - delta->y()
    // bottom = getRealY(0) - delta->y()
    // Вывод координат в консоль
    //delete pen;
}
QString CDraw::getMousePos()
{
    //Фцнкция возвращает строку с данными о текущем положении курсора мыши
    //над окном CDraw
    return QString::number((int)this->mousePos->x(),10)+
            ","+
            QString::number((int)this->mousePos->y(),10);

}
qreal CDraw::getRealY(qreal fakeY)
{
    // Инверсия оси Ординат в систему декарта
    return this->height()-fakeY;
}
QString CDraw::getDebugInfo()
{
    return this->strDebug+"\n";
}
QString CDraw::getPointstr(const QString str, QPointF point)
{
    return this->strDebug = str+ "("+QString::number((int)point.x(),10)+","
            +QString::number((int)point.y(),10)+")";
}
QString CDraw::getFtype()
{
    switch (this->currentFunctionType)
    {
    case 11:
        return "line";
        break;
    case 22:
        return "Porabolic";
        break;

    }
    return "zero";
}
void CDraw::translatePointToVirtual(qreal *x, qreal *y)
{
    *x-=this->delta->x();
    *y=this->getRealY(*y-this->delta->y());
}


void CDraw::onMouseMove(qreal xpos, qreal ypos)
{

    this->translatePointToVirtual(&xpos,&ypos); // Перерасчитываем координаты с учетом смещения виртуального экрана

    this->mousePos = new QPointF(xpos,ypos);
    this->pointB=this->mousePos->toPoint();
    if(this->onClicked) this->createChart(this->currentFunctionType);
}
void CDraw::setDelta(qreal xpos, qreal ypos)
{
    qreal acceleration=2;

    this->delta->rx()=-acceleration*xpos*abs(xpos)/2;
    this->delta->ry()=acceleration*ypos*abs(ypos)/2;
    this->paintBuffer();
    this->update();
    qDebug()<<"delta = "<<this->delta->toPoint();
}
void CDraw::onMouseClick(qreal xpos, qreal ypos)
{
    this->translatePointToVirtual(&xpos,&ypos); // Перерасчитываем координаты с учетом смещения виртуального экрана

    if(!this->onClicked)
    {
        // Если произведено первое нажатие, установка точки А
        this->pointA.setX(xpos);
        this->pointA.setY(ypos);
    }
    else
    {
        // Если произведено второе нажатие, установка точки B
        this->pointB.setX(xpos);
        this->pointB.setY(ypos);
    }
    this->onClicked=!this->onClicked;
    if(pointA!=pointB)this->createChart(this->currentFunctionType); // Строим и выводим график
}
int CDraw::createChart(unsigned int type)
{
    if(currentFunctionType==0) return -1;
    CChart * chart = new CChart(type);
    chart->getFromPoints(this->pointA,this->pointB); // Вызов расчета коэффициетов заданной функции
    if(this->onClicked)
    {
        this->paintTemporalChart(chart);
    }
    else
    {
        this->chartVector.push_back(chart);
        qDebug() << chartVector.count();
        this->paintBuffer();
    }
    this->update(); // Производим отрисовку
    return 1;
}
void CDraw::paintBuffer()
{
    int vectorPos = 0;
    int currentX=0;
    QPen * pen =new QPen();
    qreal xPos,yPos;
    QPainterPath * path=new QPainterPath();
    this->bufferImg.fill();
    this->bufferImg=this->bufferImg.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
    QPainter *paint = new QPainter();
    this->bufferImg.fill(QColor(255, 0, 0, 0));
    pen->setWidth(2);
    pen->setColor(QColor("white"));

    paint->begin(&this->bufferImg);
    // Далее делаем отрисовку на временный буфер
    // Перебираем все созданные графики функций
    paint->setPen(*pen);
    paint->setRenderHint(QPainter::Antialiasing);
    while (vectorPos<this->chartVector.count())
    {
        CChart* temporalChart = this->chartVector[vectorPos];
        currentX=0;
        while(currentX<this->width())
        {
            //Вычисляем позицию точки графика с переносом относительно виртуальной СК
            xPos = - this->delta->x()+currentX; // Отрабатываем смещение виртуального экрана по OX
            yPos = this->getRealY(temporalChart->getY(xPos)); // Отрабатываем инверсию по оси Ординат
            yPos+=this->delta->y(); // Отрабатываем смещение виртуального экрана по OY

            if(currentX==0) path->moveTo(0,yPos); // Если график пустой, переносим первую точку
            if(yPos<0) path->moveTo(0,yPos); // adding
            else path->lineTo(currentX,yPos); // Строим линию до каждой точки

            currentX++; // increment
        }
        vectorPos++; // Переход к следующему графику
    }
    paint->drawPath(*path);
    // Конец отрисовки
    paint->end();
    this->inforLayer->setInfo(0,"Points in chart - ",path->elementCount());
    path->clear();
    delete path;
    this->temporalLine->clear();
    delete paint;
}
void CDraw::paintTemporalChart(CChart *temporalChart)
{
    int currentX=0;
    qreal xPos,yPos;
    this->temporalLine->clear();
    while(currentX<this->width())
    {
        xPos=-this->delta->x()+currentX;
        yPos = this->getRealY(temporalChart->getY(xPos)); // Отрабатываем инверсию по оси Ординат
        yPos+=this->delta->y(); // Отрабатываем смещение виртуального экрана по OY
        if(currentX==0) this->temporalLine->moveTo(0,yPos); // Если график пустой, переносим первую точку
        this->temporalLine->lineTo(currentX,yPos);
        currentX++;
    }
    this->update();
}
void CDraw::cleareAllCharts()
{
    while (this->chartVector.count()>0) {
        CChart* temporalChart = this->chartVector.first();
        delete temporalChart;
        chartVector.remove(0);
    }
    this->chartVector.clear();
    paintBuffer();
    this->update();
}
void CDraw::setFtype(unsigned int type)
{
    this->currentFunctionType+=11;
    if(this->currentFunctionType>22)this->currentFunctionType=11;
}





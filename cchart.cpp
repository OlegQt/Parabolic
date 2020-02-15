#include "cchart.h"

CChart::CChart(unsigned int functionType):type(functionType)
{
    this->chartPath=new QPainterPath();
}

CChart::CChart(unsigned int type, qreal factorA, qreal factorB, qreal factorC):
    type(type),factorA(factorA),factorB(factorB),factorC(factorC)
{

}

void CChart::getFromPoints(QPointF pointA, QPointF pointB)
{
    switch (this->type)
    {
    case 22: // If porabolick function
        // Find variables for parbolic function
        // A=(Yb-Ya)/((Xa-Xb)*(Xa-Xb));
        // B=-2*A*Xa;
        // C=Ya+A*Xa*Xa;
        this->factorA=(pointB.y()-pointA.y())/qPow((pointA.x()-pointB.x()),2);
        this->factorB=-2*factorA*pointA.x();
        this->factorC=pointA.y()+factorA*qPow(pointA.x(),2);
        break;
    case 11: // If line function y=k*x+b
        // A=k=(Yb-Ya)/(Xb-Xa)
        // b=Ya-k*Xa
        this->factorA=(pointB.y()-pointA.y())/(pointB.x()-pointA.x());
        this->factorB=pointA.y()-(factorA*pointA.x());
        break;
    }
}

qreal CChart::getY(qreal X)
{
    switch (this->type)
    {
    case 22:
        return factorA*qPow(X,2)+factorB*X+factorC;
        break;
    case 11:
        return factorA*X+factorB;
        break;
    }

    return 0;
}

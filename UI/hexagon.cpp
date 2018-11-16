#include "hexagon.hh"
#include <iostream>
Hexagon::Hexagon()
{

}



QRectF Hexagon::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                          20 + penWidth, 20 + penWidth);
}

// Polygon vertex calculator, radius 100
// HUOM! y axis on positiivinen alaspäin.

static const QPointF points[6] = {
    QPointF(50/2,-87/2),
    QPointF(-50/2,-87/2),
    QPointF(-100/2,0),
    QPointF(-50/2,87/2),
    QPointF(50/2,87/2),
    QPointF(100/2,0)
};

//2nd layer keskipistehexagon, kulma 30 astetta
QPointF layer2hex[6] = {
    QPointF(75,-43),
    QPointF(0,-87),
    QPointF(-75,-44),
    QPointF(-75,43),
    QPointF(0,87),
    QPointF(75,44)
};
//3rd layer keskipistehexagon, kulma 0 astetta
QPointF layer3hexA[6] = {
    QPointF(150,0),
    QPointF(75,-130),
    QPointF(-75,-130),
    QPointF(-150,0),
    QPointF(-75,130),
    QPointF(75,130)
};

//3rd layer keskipistehexagon, kulma 30 astetta
QPointF layer3hexB[6] = {
    QPointF(152,-87),
    QPointF(0,-175),
    QPointF(-152,-88),
    QPointF(-152,87),
    QPointF(0,175),
    QPointF(152,88)
};

//Hexagonien keskipisteet, tässä 7 hexagonin mappi

static const QPointF keskipisteet[7] = {
    QPointF(0,0),
    QPointF(75,-43),
    QPointF(0,-87),
    QPointF(-75,-44),
    QPointF(-75,43),
    QPointF(0,87),
    QPointF(75,44)
};

//19 hexagonin mappi
static const QPointF keskipisteet2[19] = {
    QPointF(0,0),

    //2nd layer
    QPointF(75,-43),
    QPointF(0,-87),
    QPointF(-75,-44),
    QPointF(-75,43),
    QPointF(0,87),
    QPointF(75,44),

    //3rd layer A
    QPointF(150,0),
    QPointF(75,-130),
    QPointF(-75,-130),
    QPointF(-150,0),
    QPointF(-75,130),
    QPointF(75,130),

    //3rd layer B
    QPointF(152,-87),
    QPointF(0,-175),
    QPointF(-152,-88),
    QPointF(-152,87),
    QPointF(0,175),
    QPointF(152,88)

};




void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //asetetaan midpointin perusteella hexagonin pisteet, ja piirretään hexagoni midpointin ympärille.
    for (QPointF midpoint : keskipisteet2){

        QPointF point1;
        point1.setX(midpoint.x()+50/2);
        point1.setY(midpoint.y()-87/2);

        QPointF point2;
        point2.setX(midpoint.x()-50/2);
        point2.setY(midpoint.y()-87/2);

        QPointF point3;
        point3.setX(midpoint.x()-100/2);
        point3.setY(midpoint.y());

        QPointF point4;
        point4.setX(midpoint.x()-50/2);
        point4.setY(midpoint.y()+87/2);

        QPointF point5;
        point5.setX(midpoint.x()+50/2);
        point5.setY(midpoint.y()+87/2);

        QPointF point6;
        point6.setX(midpoint.x()+100/2);
        point6.setY(midpoint.y());

        QPointF temphex[6] = {
            point1,
            point2,
            point3,
            point4,
            point5,
            point6
        };



        painter->drawPolygon(temphex, 6);
        /*
        painter->drawPolygon(layer2hex, 6);
        painter->drawPolygon(layer3hexA, 6);
        painter->drawPolygon(layer3hexB, 6);
        */
    }
}

#include "hexagon.hh"
#include <iostream>
#include <math.h>

Hexagon::Hexagon()
{

}



QRectF Hexagon::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                          20 + penWidth, 20 + penWidth);
}

// HEX_SIZE on matka keskipisteestä kulmaan.

const int HEX_SIZE = 50;

const int HEX_WIDTH = 2 * HEX_SIZE;

const int HEX_HEIGHT = sqrt(3) * HEX_SIZE;

// Polygon vertex calculator, radius 100
// HUOM! y axis on positiivinen alaspäin.

//**************************************//
//          KESKIPISTE-LAYERIT          //
//**************************************//


//2nd layer keskipistehexagon, kulma 30 astetta
QPointF layer2hex[6] = {
    QPointF(HEX_WIDTH*3/4, -HEX_HEIGHT/2),
    QPointF(0, -HEX_HEIGHT),
    QPointF(-HEX_WIDTH*3/4, -HEX_HEIGHT/2),
    QPointF(-HEX_WIDTH*3/4, HEX_HEIGHT/2),
    QPointF(0, HEX_HEIGHT),
    QPointF(HEX_WIDTH*3/4, HEX_HEIGHT/2)
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

//**************************************//
//     KESKIPISTEET KOKONAISUUTENA      //
//**************************************//


// 7 Hexin midpoint array

static const QPointF keskipisteet[7] = {
    // (Sama kuin layer2hex, mutta origo lisätty.
    QPointF(0,0),
    QPointF(HEX_WIDTH*3/4, -HEX_HEIGHT/2),
    QPointF(0, -HEX_HEIGHT),
    QPointF(-HEX_WIDTH*3/4, -HEX_HEIGHT/2),
    QPointF(-HEX_WIDTH*3/4, HEX_HEIGHT/2),
    QPointF(0, HEX_HEIGHT),
    QPointF(HEX_WIDTH*3/4, HEX_HEIGHT/2)
};

// 19 hexin midpoint array

static const QPointF keskipisteet2[19] = {
    QPointF(0,0),

    //2nd layer Hex
    QPointF(HEX_WIDTH*3/4, -HEX_HEIGHT/2),
    QPointF(0, -HEX_HEIGHT),
    QPointF(-HEX_WIDTH*3/4, -HEX_HEIGHT/2),
    QPointF(-HEX_WIDTH*3/4, HEX_HEIGHT/2),
    QPointF(0, HEX_HEIGHT),
    QPointF(HEX_WIDTH*3/4, HEX_HEIGHT/2),

    //3rd layer Hex A
    QPointF(150,0),
    QPointF(75,-130),
    QPointF(-75,-130),
    QPointF(-150,0),
    QPointF(-75,130),
    QPointF(75,130),

    //3rd layer Hex B
    QPointF(152,-87),
    QPointF(0,-175),
    QPointF(-152,-88),
    QPointF(-152,87),
    QPointF(0,175),
    QPointF(152,88)

};




void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //Asetetaan midpointin perusteella hexagonin pisteet, ja piirretään hexagoni midpointin ympärille.
    for (QPointF midpoint : keskipisteet2){

        QPointF point1;
        point1.setX( midpoint.x() + HEX_WIDTH / 4 );
        point1.setY( midpoint.y() - HEX_HEIGHT / 2 );

        QPointF point2;
        point2.setX( midpoint.x() - HEX_WIDTH / 4 );
        point2.setY( midpoint.y() - HEX_HEIGHT / 2);

        QPointF point3;
        point3.setX( midpoint.x() - HEX_WIDTH / 2 );
        point3.setY( midpoint.y() );

        QPointF point4;
        point4.setX( midpoint.x() - HEX_WIDTH / 4 );
        point4.setY( midpoint.y() + HEX_HEIGHT / 2 );

        QPointF point5;
        point5.setX( midpoint.x() + HEX_WIDTH / 4 );
        point5.setY( midpoint.y() + HEX_HEIGHT / 2 );

        QPointF point6;
        point6.setX( midpoint.x() + HEX_WIDTH / 2 );
        point6.setY( midpoint.y() );

        QPointF TempHex[6] = {
            point1,
            point2,
            point3,
            point4,
            point5,
            point6
        };

        painter->drawPolygon(TempHex, 6);


        /*
        std::cout << HEX_WIDTH << std::endl;
        int counter = 1;
        for (QPointF point : layer2hex ) {
            std::cout << point.x() << " <-- X " << point.y() << " <-- Y --- Counter --> " << counter << std::endl;
            counter++;
        }
        */



        /*
        painter->drawPolygon(layer2hex, 6);
        painter->drawPolygon(layer3hexA, 6);
        painter->drawPolygon(layer3hexB, 6);
        */
    }
}

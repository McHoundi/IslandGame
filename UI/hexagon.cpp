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

const int HEX_SIZE = 30;

const int HEX_WIDTH = 2 * HEX_SIZE;

const int HEX_HEIGHT = sqrt(3) * HEX_SIZE;


QPointF Hexagon::move_midpoint(QPointF midpoint_marker, std::string direction) {
    //Directionit merkataan ilmansuunnilla: North, South, Northwest, jne.
    if (direction == "N") {
        //Tässä miinustetaan, koska y on negatiivinen ylöspäin.
        midpoint_marker.setY( midpoint_marker.y() - HEX_HEIGHT );
    } else if (direction == "S") {
        midpoint_marker.setY( midpoint_marker.y() + HEX_HEIGHT );
    } else if (direction == "SW") {
        midpoint_marker.setX( midpoint_marker.x() - HEX_WIDTH * 3/4 );
        midpoint_marker.setY( midpoint_marker.y() + HEX_HEIGHT / 2) ;
    } else if (direction == "SE") {
        midpoint_marker.setX( midpoint_marker.x() + HEX_WIDTH * 3/4 );
        midpoint_marker.setY( midpoint_marker.y() + HEX_HEIGHT / 2) ;
    } else if (direction == "NW") {
        midpoint_marker.setX( midpoint_marker.x() - HEX_WIDTH * 3/4 );
        midpoint_marker.setY( midpoint_marker.y() - HEX_HEIGHT / 2) ;
    } else if (direction == "NE") {
        midpoint_marker.setX( midpoint_marker.x() + HEX_WIDTH * 3/4 );
        midpoint_marker.setY( midpoint_marker.y() - HEX_HEIGHT / 2) ;
    }
    return midpoint_marker;
}

void Hexagon::draw_map(){
    //Testausta varten:
    int layers;
    std::cout << "Set number of layers: ";
    std::cin >> layers;

}


//Funktiossa kierrämme ympyrämäisesti karttaa läpi, lähtien keskiruudusta, ja kerätään palojen keskipisteet täten talteen.
Hexagon::TempStruct Hexagon::determine_midpoints(TempStruct midpoint_vessel, int hexagon_amount){
    int hex_counter = 0;
    int layer_counter = 1;

    QPointF midpoint_marker(0,0);

    midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;


    while ( hex_counter < hexagon_amount  ) {

        // Siirrytään loopin alussa seuraavaan layeriin.
        layer_counter++;
        midpoint_marker = move_midpoint(midpoint_marker, "N");
        hex_counter++;
        midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;

        // side_hops on hyppyjen (tai askelten) määrä, mitä tarvitaan päästäksemme jonkin layerin "sivun" päästä päähän.
        // Koska layerin numero on sama kuin sivujen määrä, side_hops on yksi vähemmän kuin layerin numero.
        int side_hops = layer_counter - 1;
        int i;

        //Seuraavat for-loopit liikuttavat keskipiste-merkkiä jokaisen sivun läpi, kiertäen koko layerin.
        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SW");
            hex_counter++;
            midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "S");
            hex_counter++;
            midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SE");
            hex_counter++;
            midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NE");
            hex_counter++;
            midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "N");
            hex_counter++;
            midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NW");
            hex_counter++;
            midpoint_vessel.keskipiste_array[hex_counter] = midpoint_marker;
        }


    }

    return midpoint_vessel;
}


void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
{


    // START OF "TESTAUSTA" //

    int layers = 2;
    //std::cout << "Set number of layers: ";
    //std::cin >> layers;

    // HEXAGON COUNTER //
    // Hexagons muuttuja on lähtöön 1, koska keskilaattaa ei muuten lasketa algoritmiin
    int hexagons = 1;
    int layer_hexes;
    for ( int i = layers; i != 0; i-- ) {
        layer_hexes = (i-1) * 6;
        std::cout << layer_hexes << " " << i << std::endl;
        hexagons += layer_hexes;
        std::cout << hexagons << std::endl;
    }
    std::cout << "Number of hexes in a " << layers << "-layer hexagon map is : " << hexagons << std::endl;

    TempStruct midpoint_vessel;

    midpoint_vessel = determine_midpoints(midpoint_vessel, hexagons);



    // END OF "TESTAUSTA" //

    //Asetetaan midpointin perusteella hexagonin pisteet, ja piirretään hexagoni midpointin ympärille.

    //alla oleva toimii vielä jotenkin taulukolla keskipisteet2

    for (QPointF midpoint : midpoint_vessel.keskipiste_array ){

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

        //painter->setPen(0.5);
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

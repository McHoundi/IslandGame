#include "pixmapgraphics.hh"

pixmapgraphics::pixmapgraphics()
{

}


void pixmapgraphics::setPicture(std::string type)
{
    if (type == "dolphin") {
        QPixmap pixi(":/images/dolphin.png");
        pixi = pixi.scaled(0.75*HEX_SIZE, 0.75*HEX_SIZE);
        setPixmap(pixi);
    } else if (type == "shark") {
        QPixmap pixi(":/images/shark.png");
        pixi = pixi.scaled(0.75*HEX_SIZE, 0.75*HEX_SIZE);
        setPixmap(pixi);
    } else if (type == "kraken") {
        QPixmap pixi(":/images/kraken.png");
        pixi = pixi.scaled(0.75*HEX_SIZE, 0.75*HEX_SIZE);
        setPixmap(pixi);
    } else if (type == "seamunster") {
        QPixmap pixi(":/images/seamonster.png");
        pixi = pixi.scaled(0.75*HEX_SIZE, 0.75*HEX_SIZE);
        setPixmap(pixi);
    } else if (type == "vortex") {
        QPixmap pixi(":/images/vortex.png");
        pixi = pixi.scaled(0.75*HEX_SIZE, 0.75*HEX_SIZE);
        setPixmap(pixi);
    } else if (type == "boat") {
        QPixmap pixi(":/images/boat.png");
        pixi = pixi.scaled(0.75*HEX_SIZE, 0.75*HEX_SIZE);
        setPixmap(pixi);
    }
}

void pixmapgraphics::movePicture(QPointF coords)
{
    QPointF offset = coords;
    offset.operator -=(QPointF(0.6*HEX_SIZE, 0.6*HEX_SIZE));
    this->setOffset(offset);
}

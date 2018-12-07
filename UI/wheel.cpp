#include "wheel.hh"

wheel::wheel()
{

    QPixmap Dolph1Pix(":/images/kdolph1.png");
    Dolph1Pix = Dolph1Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Dolph1Pix);

    QPixmap Dolph2Pix(":/images/kdolph2.png");
    Dolph2Pix = Dolph2Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Dolph2Pix);

    QPixmap Dolph3Pix(":/images/kdolph3.png");
    Dolph3Pix = Dolph3Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Dolph3Pix);

    QPixmap DolphDPix(":/images/kdolphD.png");
    DolphDPix = DolphDPix.scaled(QSize(250,250));
    pixmaps_.push_back(DolphDPix);

    QPixmap Shark1Pix(":/images/kshark1.png");
    Shark1Pix = Shark1Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Shark1Pix);

    QPixmap Shark2Pix(":/images/kshark2.png");
    Shark2Pix = Shark2Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Shark2Pix);

    QPixmap Shark3Pix(":/images/kshark3.png");
    Shark3Pix = Shark3Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Shark3Pix);

    QPixmap SharkDPix(":/images/ksharkD.png");
    SharkDPix = SharkDPix.scaled(QSize(250,250));
    pixmaps_.push_back(SharkDPix);

    QPixmap Kraken1Pix(":/images/kkraken1.png");
    Kraken1Pix = Kraken1Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Kraken1Pix);

    QPixmap Kraken2Pix(":/images/kkraken2.png");
    Kraken2Pix = Kraken2Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Kraken2Pix);

    QPixmap Kraken3Pix(":/images/kkraken3.png");
    Kraken3Pix = Kraken3Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Kraken3Pix);

    QPixmap KrakenDPix(":/images/kkrakenD.png");
    KrakenDPix = KrakenDPix.scaled(QSize(250,250));
    pixmaps_.push_back(KrakenDPix);

    QPixmap Seamonster1Pix(":/images/kseamonster1.png");
    Seamonster1Pix = Seamonster1Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Seamonster1Pix);

    QPixmap Seamonster2Pix(":/images/kseamonster2.png");
    Seamonster2Pix = Seamonster2Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Seamonster2Pix);

    QPixmap Seamonster3Pix(":/images/kseamonster3.png");
    Seamonster3Pix = Seamonster3Pix.scaled(QSize(250,250));
    pixmaps_.push_back(Seamonster3Pix);

    QPixmap SeamonsterDPix(":/images/kseamonsterD.png");
    SeamonsterDPix = SeamonsterDPix.scaled(QSize(250,250));
    pixmaps_.push_back(SeamonsterDPix);

}

void wheel::setPicture( std::pair<std::string,std::string> pari)
{
    if (pari.first == "dolphin") {
        if (pari.second == "1") {
            setPixmap(pixmaps_.at(0));
        } else if (pari.second == "2") {
            setPixmap(pixmaps_.at(1));
        } else if (pari.second == "3") {
            setPixmap(pixmaps_.at(2));
        } else if (pari.second == "D")
            setPixmap(pixmaps_.at(3));
    } else if (pari.first == "shark") {
        if (pari.second == "1") {
            setPixmap(pixmaps_.at(4));
        } else if (pari.second == "2") {
            setPixmap(pixmaps_.at(5));
        } else if (pari.second == "3") {
            setPixmap(pixmaps_.at(6));
        } else if (pari.second == "D")
            setPixmap(pixmaps_.at(7));
    } else if (pari.first == "kraken") {
        if (pari.second == "1") {
            setPixmap(pixmaps_.at(8));
        } else if (pari.second == "2") {
            setPixmap(pixmaps_.at(9));
        } else if (pari.second == "3") {
            setPixmap(pixmaps_.at(10));
        } else if (pari.second == "D")
            setPixmap(pixmaps_.at(11));
    } else if (pari.first == "seamunster") {
        if (pari.second == "1") {
            setPixmap(pixmaps_.at(12));
        } else if (pari.second == "2") {
            setPixmap(pixmaps_.at(13));
        } else if (pari.second == "3") {
            setPixmap(pixmaps_.at(14));
        } else if (pari.second == "D")
            setPixmap(pixmaps_.at(15));
    }
}

#include "resultdialog.hh"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
}

void ResultDialog::set_info(std::map<int, int> pointMap, std::vector<std::shared_ptr<Common::IPlayer>> playervect)
{
    playerPoints_ = pointMap;
    playerVector_ = playervect;

    std::vector<std::shared_ptr<Common::IPlayer>>::iterator playerIter = playervect.begin();
    auto end = playervect.end();
    for ( playerIter; playerIter != end; ++playerIter) {
        int points;
        int playerID = (*playerIter)->getPlayerId();
        if ( pointMap.find(playerID) == pointMap.end() ) {
            // pelaaja ei saanut pisteitä
            points = 0;
        } else {
            points = pointMap.at(playerID);
        }

        // Asetetaan pisteet oikealle pelaajalle
        if ( playerID == 1001 ) {
            ui->Player1PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player1PointsLabel->show();
            ui->Player1Label->show();
        } else if ( playerID == 1002 ) {
            ui->Player1PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player1PointsLabel->show();
            ui->Player2Label->show();
        } else if ( playerID == 1003 ) {
            ui->Player1PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player1PointsLabel->show();
            ui->Player3Label->show();
        } else if ( playerID == 1004 ) {
            ui->Player1PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player1PointsLabel->show();
            ui->Player4Label->show();
        }



    }



}



ResultDialog::~ResultDialog()
{
    delete ui;
}

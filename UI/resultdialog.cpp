#include "resultdialog.hh"
#include "ui_resultdialog.h"
#include "iostream"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    ui->Player1Label->hide();
    ui->Player2Label->hide();
    ui->Player3Label->hide();
    ui->Player4Label->hide();
    ui->Player1PointsLabel->hide();
    ui->Player2PointsLabel->hide();
    ui->Player3PointsLabel->hide();
    ui->Player4PointsLabel->hide();

}

void ResultDialog::set_info(std::map<int, int> pointMap, std::vector<std::shared_ptr<Common::IPlayer>> playervect)
{
    std::cout << playervect.size() << std::endl;

    for ( auto playerIter : playervect ) {
        int points;
        int playerID = playerIter->getPlayerId();
        if ( pointMap.find(playerID) == pointMap.end() ) {
            // pelaaja ei saanut pisteitä
            points = 0;
            std::cout << playerID << std::endl;
        } else {
            points = pointMap.at(playerID);
        }

        // Asetetaan pisteet oikealle pelaajalle
        if ( playerID == 1001 ) {
            ui->Player1PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player1PointsLabel->show();
            ui->Player1Label->show();
        } else if ( playerID == 1002 ) {
            ui->Player2PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player2PointsLabel->show();
            ui->Player2Label->show();
        } else if ( playerID == 1003 ) {
            ui->Player3PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player3PointsLabel->show();
            ui->Player3Label->show();
        } else if ( playerID == 1004 ) {
            ui->Player4PointsLabel->setText(QString::fromStdString(std::to_string(points)));
            ui->Player4PointsLabel->show();
            ui->Player4Label->show();
        }
    }



}



ResultDialog::~ResultDialog()
{
    delete ui;
}

#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "player.hh"
#include "gameengine.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "vector"
#include <QDebug>
#include <QLayout>
#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include "iostream"
#include "QDebug"
#include "startdialog.hh"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StartDialog dialogi;
    QGraphicsScene* scene = new QGraphicsScene;

    std::shared_ptr<Student::GameBoard> boardPtr = std::make_shared<Student::GameBoard>();
    std::shared_ptr<GameState> statePtr = std::make_shared<GameState>();


    connect(&dialogi, &StartDialog::runClicked, this, &MainWindow::get_inputs);
    dialogi.exec();

    std::vector<std::shared_ptr<Common::IPlayer> >  pelaajat = initialize_players();
    Logic::GameEngine Moottori(boardPtr, statePtr, pelaajat);


    statePtr->set_boardPTR(boardPtr);

    boardPtr->set_scene(scene);

    draw_map(boardPtr, scene);





    // ** addPawn TESTAUS
    boardPtr->addPawn(1001,11,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1002,21,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1003,31,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1004,41,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1005,51,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1006,61,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1007,71,Common::CubeCoordinate(0,0,0));
    boardPtr->addPawn(1008,81,Common::CubeCoordinate(0,0,0));


     // ** addPawn TESTAUS

    ui->graphicsView->setScene(scene);


}

void MainWindow::get_inputs(int playerCount){
    playerCount_ = playerCount;
}

std::vector<std::shared_ptr<Common::IPlayer>> MainWindow::initialize_players()
{

    int PlayerID = 1001;
    int i;
    std::vector<std::shared_ptr<Common::IPlayer> > playerVector;
    for ( i = playerCount_ ; i != 0; i-- ) {
        std::shared_ptr<Common::IPlayer> ipelaaja = std::make_shared<Player>(PlayerID);
        playerVector.push_back(ipelaaja);
        PlayerID++;
    }
    return playerVector;

}

void MainWindow::draw_map(std::shared_ptr<Student::GameBoard> boardPtr, QGraphicsScene* scene)
{

    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexPtrs;
    hexPtrs = boardPtr->get_hexPointers();

    std::string type;
    QBrush brush;
    Common::CubeCoordinate cubecoords;
    std::shared_ptr<Common::Hex> hex_pointer;

    for (auto const& it : hexPtrs ) {

            hex_pointer = it.second;
            cubecoords = it.first;
            if( hex_pointer != nullptr ) {
                type = hex_pointer->getPieceType();
                if (type == "Peak") {
                    brush.setColor(Qt::darkGray);
                } else if (type == "Mountain") {
                    brush.setColor(Qt::lightGray);
                } else if (type == "Forest") {
                    brush.setColor(Qt::green);
                } else if (type == "Beach") {
                    brush.setColor(Qt::yellow);
                } else if (type == "Coral") {
                    brush.setColor(Qt::magenta);
                } else if (type == "Water") {
                    brush.setColor(Qt::cyan);
                } else {
                    std::cout << "Unrecognized type!" << std::endl;
                }

                hexgraphics* HexItem = new hexgraphics;
                HexItem->set_hexptr(hex_pointer);
                HexItem->set_coords(boardPtr->cube_to_square(cubecoords));

                brush.setStyle(Qt::SolidPattern);
                HexItem->setBrush(brush);
                scene->addItem(HexItem);
            }
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}



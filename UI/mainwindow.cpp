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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;


    std::shared_ptr<Student::GameBoard> boardPtr = std::make_shared<Student::GameBoard>();
    std::shared_ptr<Common::IGameState> statePtr;
    std::vector<std::shared_ptr<Common::IPlayer> >  pelaajat;


    Logic::GameEngine Moottori(boardPtr, statePtr, pelaajat);
    draw_map(boardPtr, scene);


    ui->graphicsView->setScene(scene);


}

void MainWindow::draw_map(std::shared_ptr<Student::GameBoard> boardPtr, QGraphicsScene* scene)
{

    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexPtrs;
    hexPtrs = boardPtr->get_hexPointers();

    std::string type;
    QBrush brush;
    Common::CubeCoordinate cubecoords;
    std::shared_ptr<Common::Hex> hex_pointer;
    int counter = 0;
    //std::cout << hexPtrs.size() << std::endl;

    for (auto const& it : hexPtrs ) {
            //std::cout << counter << std::endl;
            counter++;
            hex_pointer = it.second;
            cubecoords = it.first;
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

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::spawnObjects() {

    //auto pObj = std::make_shared<FastBall>();
    //engine_->registerObject(pObj);
    //auto pGraph = new PiirtoTesti(pObj);
    //graphics_.push_back(pGraph);
    //view_->scene()->addItem(pGraph);

//}

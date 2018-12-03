#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "player.hh"
#include "gameengine.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "pawngraphics.hh"
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
#include "QGraphicsPixmapItem"
#include "QGraphicsEllipseItem"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StartDialog dialogi;
    QGraphicsScene* scene = new QGraphicsScene;

    std::shared_ptr<Student::GameBoard> boardPtr = std::make_shared<Student::GameBoard>();
    std::shared_ptr<Common::IGameState> statePtr;
    std::vector<std::shared_ptr<Common::IPlayer> >  pelaajat;

    connect(&dialogi, &StartDialog::runClicked, this, &MainWindow::get_inputs);




    Logic::GameEngine Moottori(boardPtr, statePtr, pelaajat);

    draw_map(boardPtr, scene);
    ui->graphicsView->setScene(scene);

    dialogi.exec();
}

void MainWindow::get_inputs(int playerCount){
    std::cout << playerCount << std::endl;
    playerCount_ = playerCount;
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

                QPointF XYCOORDS = boardPtr->cube_to_square(cubecoords);

                brush.setStyle(Qt::SolidPattern);
                HexItem->setBrush(brush);
                scene->addItem(HexItem);

                QPixmap actor(":/images/shark.png");
                actor = actor.scaled(QSize(15,15));
                QGraphicsPixmapItem* kuva = new QGraphicsPixmapItem(actor);
                QPointF offset = boardPtr->cube_to_square(cubecoords);
                offset.operator -=(QPointF(12, 12));
                kuva->setOffset(offset);
                scene->addItem(kuva);


                QPixmap kiekkoPix(":/images/kdolph1.png");
                kiekkoPix = kiekkoPix.scaled(QSize(250,250));
                QGraphicsPixmapItem* kiekko = new QGraphicsPixmapItem(kiekkoPix);
                kiekko->setOffset(QPointF(350, 0));
                scene->addItem(kiekko);

                pawngraphics* pawni1 = new pawngraphics;

                pawni1->setRect(XYCOORDS.x()+4,XYCOORDS.y()+4,8,8);
                brush.setStyle(Qt::SolidPattern);
                brush.setColor(Qt::red);
                pawni1->setBrush(brush);
                scene->addItem(pawni1);

                pawngraphics* pawni2 = new pawngraphics;

                pawni2->setRect(XYCOORDS.x()+4,XYCOORDS.y()-6,8,8);
                brush.setStyle(Qt::SolidPattern);
                brush.setColor(Qt::blue);
                pawni2->setBrush(brush);
                scene->addItem(pawni2);

                pawngraphics* pawni3 = new pawngraphics;

                pawni3->setRect(XYCOORDS.x()-6,XYCOORDS.y()+4,8,8);
                brush.setStyle(Qt::SolidPattern);
                brush.setColor(Qt::white);
                pawni3->setBrush(brush);
                scene->addItem(pawni3);
            }
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

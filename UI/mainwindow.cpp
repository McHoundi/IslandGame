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

	// Aloitusikkunan OK-nappi on kytketty tähän.
	connect(&dialogi, &StartDialog::runClicked, this, &MainWindow::get_inputs); 
	
    std::shared_ptr<Student::GameBoard> boardPtr = std::make_shared<Student::GameBoard>();
    std::shared_ptr<GameState> statePtr;
    std::vector<std::shared_ptr<Common::Player> > pelaajat = initialize_players();
	
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

std::vector<std::shared_ptr<Player> > initialize_players() 
{
	int PlayerID = 1001
	std::vector<std::shared_ptr<Player> > playerVector;
	for ( i = playerCount_; i != 0; i-- ) {
		playerVector.push_back(std::make_shared<Player>(PlayerID));
		PlayerID++;
	}
	return playerVector;

}

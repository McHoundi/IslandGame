#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "player.hh"
#include "gameengine.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "pawngraphics.hh"
#include "wheel.hh"
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
#include "igamerunner.hh"
#include "initialize.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StartDialog dialogi;
    scene1_ = new QGraphicsScene;


	
    std::shared_ptr<Student::GameBoard> boardPtr = std::make_shared<Student::GameBoard>();

    std::shared_ptr<GameState> statePtr = std::make_shared<GameState>();


    connect(&dialogi, &StartDialog::runClicked, this, &MainWindow::get_inputs);
    dialogi.exec();

    std::vector<std::shared_ptr<Common::IPlayer> >  pelaajat = initialize_players();
    boardPtr->set_scene(scene1_);
    runner_ = Common::Initialization::getGameRunner(boardPtr, statePtr, pelaajat);


    statePTR_ = statePtr;
    boardPTR_ = boardPtr;
    playerVector_ = pelaajat;



    for ( std::shared_ptr<Common::IPlayer> pelaaja : pelaajat ) {
        initialize_pawns(pelaaja);
    }
    draw_map();

    runner_->flipTile(Common::CubeCoordinate(0, -5, 5));
    runner_->flipTile(Common::CubeCoordinate(1, -5, 4));

    statePTR_->changeGamePhase(Common::GamePhase::SPINNING);



    ui->graphicsView->setScene(scene1_);

    //run_movement_phase();

}

void MainWindow::get_inputs(int playerCount){
    playerCount_ = playerCount;
}

std::vector<std::shared_ptr<Common::IPlayer>> MainWindow::initialize_players()
{

    int PlayerID = 1001;
    int i;
    std::vector<std::string> playerColors{};


    std::vector<std::shared_ptr<Common::IPlayer> > playerVector;
    std::shared_ptr<Common::IPlayer> IPelaaja;
    for ( i = playerCount_ ; i != 0; i-- ) {
        IPelaaja = std::make_shared<Player>(PlayerID);
        playerVector.push_back(IPelaaja);
        PlayerID++;
    }
    ;

    return playerVector;

}

void MainWindow::initialize_pawns(std::shared_ptr<Common::IPlayer> pelaaja)
{
    // The mountainpeak has been made unvailable for players to enter,
    // so at the start of the game, we're choosing the spawn tile for each pawn from a random neighbouring tile.



    int GamerID = pelaaja->getPlayerId();
    std::cout << "GamerID: " << GamerID << std::endl;
    int basePawnID = GamerID - 1000;
    int Pawnid = basePawnID * 10 + 1; // For 1st player, of playerid 1001, this equates to 11 (FOR SOME REASON, WHEN WE MULTIPLY BY ONE, IT MULTPLIES BY 10)

    //We create 3 pawns for each player.
    int i = 0;
    for ( ; i < 3; i++ ) {
        boardPTR_->addPawn(GamerID,Pawnid,Common::CubeCoordinate(0,0,0));
        Pawnid++;
    }

}

void MainWindow::run_game()
{
    while ( true ) {

    }
}

void MainWindow::run_movement_phase()
{
    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
    int i = 0;

    for ( std::shared_ptr<Common::IPlayer> pelaaja : playerVector_) {
        while ( pelaaja->getActionsLeft() > 0 ) {
            //Tässä pitäisi vain odottaa että actionit loppuvat
        }
        std::cout << "WHILE LOOPPI LOPPU" << std::endl;
    }
}


void MainWindow::draw_map()
{

    wheel* kiekko = new wheel;
    kiekko->setPicture();
    kiekko->setOffset(QPointF(350, 0));
    scene1_->addItem(kiekko);

    for (auto const& it : boardPTR_->get_hexItems() ) {
              hexgraphics* HexItem = it.second;
                connect(HexItem, &hexgraphics::hexClicked, this, &MainWindow::hex_chosen);
            }
}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::hex_chosen(std::shared_ptr<Common::Hex> hexi)
{
    if ( statePTR_->currentGamePhase() == Common::GamePhase::MOVEMENT ) {

        if ( hexi->getPawnAmount() > 0 && highlightedPawn_ == nullptr ) {
             int current_player = statePTR_->currentPlayer();
             std::vector<std::shared_ptr<Common::Pawn>> pawnlist = hexi->getPawns();
             for ( auto pawn : pawnlist ) {
                 if ( current_player == pawn->getPlayerId() ) {
                     highlightedPawn_ = pawn;
                     highlightedHex_ = hexi;
                     break;
                 }
             if ( highlightedPawn_ != nullptr ) {
                 std::cout << "Player " << current_player << " has no pawns in this tile!" << std::endl;
             } else {
                 //Hex&Pawn highlighted!!
             }

            }
        } else if ( highlightedPawn_ != nullptr) {

            //boardPTR_->movePawn(highlightedPawn_->getId(), hexi->getCoordinates());
            runner_->movePawn(highlightedPawn_->getCoordinates(), hexi->getCoordinates(), highlightedPawn_->getId());

            //check if movement went through, clear highlights if it did, otherwise do nothing
            if ( highlightedPawn_->getCoordinates() == hexi->getCoordinates() ) {
                std::cout << "Pawn Moved! " << std::endl;
                std::cout << "Player: " << highlightedPawn_->getPlayerId() << " Pawn: " << highlightedPawn_->getId() << std::endl;
                highlightedPawn_ = nullptr;
                highlightedHex_ = nullptr;
            } else {
                //Do nothing;
            }


        }


    } else if ( statePTR_->currentGamePhase() == Common::GamePhase::SINKING ) {
            Common::CubeCoordinate coords = hexi->getCoordinates();
            runner_->flipTile(coords);
            hexgraphics* hexItem;
            hexItem = boardPTR_->get_hexItems().at(coords);
            QBrush waterbrush;
            waterbrush.setColor(Qt::cyan);
            waterbrush.setStyle(Qt::SolidPattern);
            hexItem->setBrush(waterbrush);

    } else if (statePTR_->currentGamePhase() == Common::GamePhase::SPINNING ) {
        Common::CubeCoordinate coords = hexi->getCoordinates();
        if ( highlightedActor_ != nullptr) {
            runner_->moveActor(highlightedHex_->getCoordinates(), coords, highlightedActor_->getId(), "1");
            highlightedHex_ = nullptr;
            highlightedActor_ = nullptr;
        } else if (highlightedTransport_ != nullptr) {
            runner_->moveTransportWithSpinner(highlightedHex_->getCoordinates(), coords, highlightedTransport_->getId(), "1");
            highlightedHex_ = nullptr;
            highlightedTransport_ = nullptr;
        } else if ( hexi->getActors().size() != 0) {
            highlightedActor_ = (hexi->getActors()).at(0);
            highlightedHex_ = hexi;
        } else if (hexi->getTransports().size() != 0)  {
            highlightedTransport_ = (hexi->getTransports()).at(0);
            highlightedHex_ = hexi;
        }



    }
}



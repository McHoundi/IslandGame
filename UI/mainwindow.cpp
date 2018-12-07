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
#include <QPushButton>



#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include "iostream"
#include "QDebug"
#include "startdialog.hh"
#include "igamerunner.hh"
#include "illegalmoveexception.hh"
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

    //Setting required variables for the game to start:
    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
    statePTR_->changePlayerTurn(1001);
    players_.at(1001)->setActionsLeft(3);

    aloitusnappi_ = new QPushButton;
    connect(aloitusnappi_, &QPushButton::clicked,this, &MainWindow::handle_startButton);

    aloitusnappi_->setGeometry(QRect(300, -300, 200, 50));
    aloitusnappi_->setText("Start Game");
    scene1_->addWidget(aloitusnappi_);

    ui->graphicsView->setScene(scene1_);

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
        players_[PlayerID] = IPelaaja;
        PlayerID++;
    }


    return playerVector;

}

void MainWindow::initialize_pawns(std::shared_ptr<Common::IPlayer> pelaaja)
{
    // The mountainpeak has been made unvailable for players to enter,
    // so at the start of the game, we're choosing the spawn tile for each pawn from a random neighbouring tile.



    int GamerID = pelaaja->getPlayerId();
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
    //set to first player's turn


}

void MainWindow::run_movement_phase(std::shared_ptr<Common::IPlayer>)
{


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
             if ( highlightedPawn_ == nullptr ) {
                 std::cout << "Player " << current_player << " has no pawns in this tile!" << std::endl;
             } else {
                 //Hex&Pawn highlighted!!
             }

            }
        } else if ( highlightedPawn_ != nullptr) {
            try {
                runner_->movePawn(highlightedPawn_->getCoordinates(), hexi->getCoordinates(), highlightedPawn_->getId());
                std::cout << "Pawn Moved! " << std::endl;
                std::cout << "Player: " << highlightedPawn_->getPlayerId() << " Pawn: " << highlightedPawn_->getId() << std::endl;
                highlightedPawn_ = nullptr;
                highlightedHex_ = nullptr;
                if (players_.at(statePTR_->currentPlayer())->getActionsLeft() <= 0) {
                    statePTR_->changeGamePhase(Common::GamePhase::SINKING);
                    std::cout << "Changed gamephase to SINKING" << std::endl;
                }
            } catch (Common::IllegalMoveException errori ) {
                std::cout << errori.msg() << std::endl;
                highlightedPawn_ = nullptr;
                highlightedHex_ = nullptr;
            }
            //boardPTR_->movePawn(highlightedPawn_->getId(), hexi->getCoordinates());


            //check if movement went through, clear highlights if it did, otherwise do nothing
            //if ( highlightedPawn_->getCoordinates() == hexi->getCoordinates() ) {

            //} else {
                //Do nothing;
            //}


        }


    } else if ( statePTR_->currentGamePhase() == Common::GamePhase::SINKING ) {
        try{
            Common::CubeCoordinate coords = hexi->getCoordinates();
            runner_->flipTile(coords);
            hexgraphics* hexItem;
            hexItem = boardPTR_->get_hexItems().at(coords);
            QBrush waterbrush;
            waterbrush.setColor(Qt::cyan);
            waterbrush.setStyle(Qt::SolidPattern);
            hexItem->setBrush(waterbrush);

            int current_player = statePTR_->currentPlayer();

            if (players_.find(current_player+1) == players_.end()) {
                statePTR_->changePlayerTurn(1001);
                players_.at(1001)->setActionsLeft(3);
            } else {
                statePTR_->changePlayerTurn(current_player+1);
                players_.at(current_player+1)->setActionsLeft(3);
            }


            std::cout << "next player: " << statePTR_->currentPlayer() << std::endl;
            statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);

        } catch (Common::IllegalMoveException errori) {
            std::cout << errori.msg() << std::endl;
        }


    } else {

    }
}

void MainWindow::handle_startButton()
{
    delete aloitusnappi_;
    std::cout << "aloitusnappia painettu" << std::endl;
    statePTR_->changePlayerTurn(1001);
    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    showEventHelper();
}

void MainWindow::showEventHelper() {
    std::cout << "AFTER MAP IS SHOWN" << std::endl;
}


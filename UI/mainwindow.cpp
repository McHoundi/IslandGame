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

    boardPTR_ = std::make_shared<Student::GameBoard>();
    boardPTR_->set_testmode_off();

    statePTR_ = std::make_shared<GameState>();


    connect(&dialogi, &StartDialog::runClicked, this, &MainWindow::get_inputs);
    dialogi.exec();

    std::vector<std::shared_ptr<Common::IPlayer> >  pelaajat = initialize_players();
    boardPTR_->set_scene(scene1_);
    runner_ = Common::Initialization::getGameRunner(boardPTR_, statePTR_, pelaajat);


    playerVector_ = pelaajat;



    for ( std::shared_ptr<Common::IPlayer> pelaaja : pelaajat ) {
        initialize_pawns(pelaaja);
    }

    draw_map();



//lisäillään nappuloita
    spinButton_ = new QPushButton;
    connect(spinButton_, &QPushButton::clicked, this, &MainWindow::handle_spinButton);
    spinButton_->setGeometry(QRect(-10, 350, 250, 50));
    spinButton_->setText("SPIN!!");
    scene1_->addWidget(spinButton_);

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


    std::vector<std::shared_ptr<Common::IPlayer> > playerVector;
    std::shared_ptr<Common::IPlayer> IPelaaja;
    for ( i = playerCount_ ; i != 0; i-- ) {
        IPelaaja = std::make_shared<Player>(PlayerID);
        playerVector.push_back(IPelaaja);
        players_[PlayerID] = IPelaaja;
        statePTR_->addPlayer(PlayerID);
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
        boardPTR_->add_pawn_to_player(Pawnid, GamerID);
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

    wheel_ = new wheel;
    wheel_->setPicture(std::make_pair("dolphin", "1"));
    wheel_->setOffset(QPointF(350, 0));
    scene1_->addItem(wheel_);

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
                } else if ( allPawnsInWater() == true ) {
                   std::cout << "All pawns in water! Can't move anymore." << std::endl;
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



            statePTR_->changeGamePhase(Common::GamePhase::SPINNING);

        } catch (Common::IllegalMoveException errori) {
            std::cout << errori.msg() << std::endl;
        }



    } else if (statePTR_->currentGamePhase() == Common::GamePhase::SPINNING && wheelSpinned_) {
        Common::CubeCoordinate coords = hexi->getCoordinates();
        if ( highlightedActor_ != nullptr) {
            std::string moves;
            if (animalMovesLeft_ == -99) {
                moves = "D";
            } else {
                moves = std::to_string(animalMovesLeft_);
            }
            std::cout << moves << std::endl; // Debug
            try {
                runner_->moveActor(highlightedHex_->getCoordinates(), coords, highlightedActor_->getId(), moves );
                unsigned int distance = cubeCoordinateDistance(highlightedHex_->getCoordinates(), coords);
                highlightedHex_ = boardPTR_->get_hexPointers().at(coords);
                animalMovesLeft_ -= distance;
                if (animalMovesLeft_ <= 0) {
                    highlightedActor_ = nullptr;
                    highlightedHex_ = nullptr;
                    wheelSpinned_ = false;

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

                 }


            } catch (Common::IllegalMoveException errori) {
                std::cout << errori.msg() << std::endl;
            }

        } else if (highlightedTransport_ != nullptr) {
            std::string moves;
            if (animalMovesLeft_ == -99) {
                moves = "D";
            } else {
                moves = std::to_string(animalMovesLeft_);
            }
            std::cout << moves << std::endl; // Debug
            try {
                runner_->moveTransportWithSpinner(highlightedHex_->getCoordinates(), coords, highlightedTransport_->getId(), moves);
                unsigned int distance = cubeCoordinateDistance(highlightedHex_->getCoordinates(), coords);
                highlightedHex_ = boardPTR_->get_hexPointers().at(coords);
                animalMovesLeft_ -= distance;
                if (animalMovesLeft_ <= 0) {
                    highlightedTransport_ = nullptr;
                    highlightedHex_ = nullptr;
                    wheelSpinned_ = false;

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

                }
            } catch (Common::IllegalMoveException errori) {
                std::cout << errori.msg() << std::endl;
            }

        } else if ( hexi->getActors().size() != 0) {
            if (hexi->getActors().at(0)->getActorType() == spinnerResult_.first) {
                highlightedActor_ = (hexi->getActors()).at(0);
                highlightedHex_ = hexi;
            } else {
                std::cout << "Wrong animal clicked" << std::endl;
            }
        } else if (hexi->getTransports().size() != 0)  {
            if (hexi->getTransports().at(0)->getTransportType() == spinnerResult_.first) {
                highlightedTransport_ = (hexi->getTransports()).at(0);
                highlightedHex_ = hexi;
            } else {
                std::cout << "Wrong animal clicked" << std::endl;
            }
        }

    }
}

void MainWindow::handle_spinButton()
{
    if (statePTR_->currentGamePhase() == Common::GamePhase::SPINNING && wheelSpinned_ == false) {
        std::pair<std::string,std::string> tulos = runner_->spinWheel();
        wheel_->setPicture(tulos);
        spinnerResult_ = tulos;
        if (boardPTR_->checkAnimalTypeExists(tulos.first)) {
            if (spinnerResult_.second != "D") {
                animalMovesLeft_ = stoi(spinnerResult_.second);
            } else {
                animalMovesLeft_ = -99;
            }
            wheelSpinned_ = true;
        } else {
            std::cout << "No animal of this type on board" << std::endl;
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
        }
    }
}

bool MainWindow::allPawnsInWater()
{
    std::map<int,std::shared_ptr<Common::Pawn>> pawnMap = boardPTR_->get_pawns();
    int playerID = statePTR_->currentPlayer();
    for (auto const& it : pawnMap ) {
        std::shared_ptr<Common::Pawn> pawni = it.second;
        if (pawni->getPlayerId() == playerID) {
            std::shared_ptr<Common::Hex> pawnHex = boardPTR_->get_hexPointers().at(pawni->getCoordinates());
            if ( pawnHex->getPieceType() != "Water" ) {
                return false; // This means that at least one of player 1's pawns are on land.
            }
        }
       }
        // for loop mennyt loppuun, joten kaikki pawnit vedessä
    return true;
}

void MainWindow::handle_startButton()
{
    delete aloitusnappi_;
    std::cout << "aloitusnappia painettu" << std::endl;
    statePTR_->changePlayerTurn(1001);
    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
    players_.at(1001)->setActionsLeft(3);
}

unsigned int MainWindow::cubeCoordinateDistance(Common::CubeCoordinate source, Common::CubeCoordinate target) const
{

    return ((abs(source.x - target.x) + abs(source.y - target.y)
             + abs(source.z - target.z)) / 2);

}

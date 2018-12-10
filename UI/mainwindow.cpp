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
#include <QScrollBar>



#include <algorithm>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include "iostream"
#include "QDebug"
#include "startdialog.hh"
#include "resultdialog.hh"
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
    playerVector_ = initialize_players();
    playerIter = playerVector_.begin();
    boardPTR_->set_scene(scene1_);
    ui->spinButton->setEnabled(false);




    infoBox* infolaatikko = new infoBox;


    infobox_ = infolaatikko;
    infobox_->setReadOnly(true);
    infobox_->setGeometry(1160,530,250,100);
    ui->gridLayout->addWidget(infobox_);

    boardPTR_->set_infoBox(infolaatikko);
    statePTR_->set_infobox(infolaatikko);





    //Lisätään nappeja

    connect(ui->spinButton, &QPushButton::clicked, this, &MainWindow::handle_spinButton);




    //Boarding action nappuloiden connectointi
    connect(ui->Pawn1BoardButton, &QPushButton::clicked, this, &MainWindow::handle_boardingButton);
    ui->Pawn1BoardButton->hide();
    connect(ui->Pawn2BoardButton, &QPushButton::clicked, this, &MainWindow::handle_boardingButton2);
    ui->Pawn2BoardButton->hide();
    connect(ui->Pawn3BoardButton, &QPushButton::clicked, this, &MainWindow::handle_boardingButton3);
    ui->Pawn3BoardButton->hide();

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

void MainWindow::initialize_runner()
{
    runner_ = Common::Initialization::getGameRunner(boardPTR_, statePTR_, playerVector_);
    for ( std::shared_ptr<Common::IPlayer> pelaaja : playerVector_ ) {
        initialize_pawns(pelaaja);
    }
    draw_map();

    // start button lisätään tässä jotta se tulostuu kartan päälle
    startButton_ = new QPushButton;
    connect(startButton_, &QPushButton::clicked,this, &MainWindow::handle_startButton);
    startButton_->setGeometry(QRect(-150, -150, 300, 75));
    startButton_->setText("Start Game");
    scene1_->addWidget(startButton_);
}


void MainWindow::draw_map()
{

    wheel_ = new wheel;
    wheel_->setPicture(std::make_pair("dolphin", "1"));
    ui->wheellabel->setPixmap(wheel_->get_pixmaps().at(0));

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
    updateTransportInfo();
    //MOVEMENT PHASE
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
             }
             if ( highlightedPawn_ == nullptr ) {
                 infobox_->printInfo("Player " + std::to_string(current_player) + " has no pawns in this tile!");

             } else {
                 //Hex&Pawn highlighted!!
             }


        } else if ( highlightedPawn_ != nullptr) {
            try {

                if (boardPTR_->pawnInTransport(highlightedPawn_)) {
                    if((highlightedHex_->getTransports().at(0))->canMove(statePTR_->currentPlayer())){
                        runner_->moveTransport(highlightedHex_->getCoordinates(), hexi->getCoordinates(),
                                               highlightedHex_->getTransports().at(0)->getId());
                        infobox_->printInfo("Moves left: " + std::to_string(players_.at(statePTR_->currentPlayer())->getActionsLeft()));
                    } else {
                        infobox_->printInfo("Player " + std::to_string(statePTR_->currentPlayer()) +
                                             "can't move this boat. Unboard before moving.");
                    }

                } else {
                    runner_->movePawn(highlightedPawn_->getCoordinates(), hexi->getCoordinates(), highlightedPawn_->getId());
                    infobox_->printInfo("Moves left: " + std::to_string(players_.at(statePTR_->currentPlayer())->getActionsLeft()));
                }

                updateTransportInfo();

                highlightedPawn_ = nullptr;
                highlightedHex_ = nullptr;
                if (players_.at(statePTR_->currentPlayer())->getActionsLeft() <= 0) {
                    statePTR_->changeGamePhase(Common::GamePhase::SINKING);
                    ui->gamephasevaluelabel->setText("SINKING");
                } else if ( allPawnsSwimming() == true ) {
                   infobox_->printInfo("All pawns in water! Can't move anymore.");

                   statePTR_->changeGamePhase(Common::GamePhase::SINKING);                 
                   ui->gamephasevaluelabel->setText("SINKING");

                }

            } catch (Common::IllegalMoveException errori ) {
                infobox_->printInfo(errori.msg() + "!");
                infobox_->printInfo("Moves left: " + std::to_string(players_.at(statePTR_->currentPlayer())->getActionsLeft()));
                highlightedPawn_ = nullptr;
                highlightedHex_ = nullptr;
            }


        }

     //SINKING PHASE

    } else if ( statePTR_->currentGamePhase() == Common::GamePhase::SINKING ) {
        try{
            updateTransportInfo();
            Common::CubeCoordinate coords = hexi->getCoordinates();
            runner_->flipTile(coords);
            hexgraphics* hexItem;
            hexItem = boardPTR_->get_hexItems().at(coords);
            QBrush waterbrush;
            waterbrush.setColor(Qt::cyan);
            waterbrush.setStyle(Qt::SolidPattern);
            hexItem->setBrush(waterbrush);

            statePTR_->changeGamePhase(Common::GamePhase::SPINNING);
            ui->gamephasevaluelabel->setText("SPINNING");
            ui->spinButton->setEnabled(true);

            //Päivitetään vielä transportInfo
            updateTransportInfo();


        } catch (Common::IllegalMoveException errori) {
            infobox_->printInfo(errori.msg() + "!");
        }


    //SPINNING PHASE

    } else if (statePTR_->currentGamePhase() == Common::GamePhase::SPINNING && wheelSpinned_) {
        Common::CubeCoordinate coords = hexi->getCoordinates();

        //Actoria liikutetaan
        if ( highlightedActor_ != nullptr) {
            std::string moves;
            if (animalMovesLeft_ == -99) {
                moves = "D";
            } else {
                moves = std::to_string(animalMovesLeft_);
                infobox_->printInfo("Moves left: " + moves);
            }
            try {


                runner_->moveActor(highlightedHex_->getCoordinates(), coords, highlightedActor_->getId(), moves );

                if ( coords == highlightedActor_->getHex()->getCoordinates() ) {
                    unsigned int distance = cubeCoordinateDistance(highlightedHex_->getCoordinates(), coords);
                    highlightedHex_ = boardPTR_->get_hexPointers().at(coords);
                    animalMovesLeft_ -= distance;
                }

                if ((animalMovesLeft_ == 0 || animalMovesLeft_ < -99)
                        && coords == highlightedActor_->getHex()->getCoordinates()) {
                    highlightedActor_ = nullptr;
                    highlightedHex_ = nullptr;
                    wheelSpinned_ = false;

                    change_player();

                    ui->spinButton->setText("SPIN!!");
                    scene1_->update();

                    std::string player = std::to_string(statePTR_->currentPlayer());
                    ui->playervaluelabel->setText(QString::fromStdString(player));
                    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
                    ui->spinButton->setEnabled(false);
                    ui->gamephasevaluelabel->setText("MOVEMENT");
                    updateTransportInfo();

                 }


            } catch (Common::IllegalMoveException errori) {
                infobox_->printInfo(errori.msg() + "!");
            }

            //Transportia liikutetaan
        } else if (highlightedTransport_ != nullptr) {
            std::string moves;
            if (animalMovesLeft_ == -99) {
                moves = "D";
            } else {
                moves = std::to_string(animalMovesLeft_);
                infobox_->printInfo("Moves left: " + moves);

            }
            try {
                std::shared_ptr<Common::Pawn> pawnptr;
                //Laitetaan delfiinin sisällä oleva pawni muistiin, mikäli siellä moinen on
                if ( highlightedTransport_->getPawnsInTransport().size() > 0 ) {
                    pawnptr = highlightedTransport_->getPawnsInTransport().at(0);
                }
                runner_->moveTransportWithSpinner(highlightedHex_->getCoordinates(), coords, highlightedTransport_->getId(), moves);

                if ( coords == highlightedTransport_->getHex()->getCoordinates() ) {
                    unsigned int distance = cubeCoordinateDistance(highlightedHex_->getCoordinates(), coords);
                    highlightedHex_ = boardPTR_->get_hexPointers().at(coords);
                    animalMovesLeft_ -= distance;
                }

                if ((animalMovesLeft_ == 0 || animalMovesLeft_ < -99) &&
                        coords == highlightedTransport_->getHex()->getCoordinates()) {
                    highlightedTransport_ = nullptr;
                    highlightedHex_ = nullptr;
                    wheelSpinned_ = false;

                    //Jos spinnattiin "D", siirretään pawni graafisesti myös
                    //uimaan removePawnFromTransport funktion avulla
                    if ( moves == "D") {
                        if ( pawnptr != nullptr ) {
                            boardPTR_->removePawnFromTransport(pawnptr->getId());
                        }
                    }

                    change_player();

                    ui->spinButton->setText("SPIN!!");
                    scene1_->update();

                    std::string player = std::to_string(statePTR_->currentPlayer());
                    ui->playervaluelabel->setText(QString::fromStdString(player));
                    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
                    ui->spinButton->setEnabled(false);
                    ui->gamephasevaluelabel->setText("MOVEMENT");
                    updateTransportInfo();

                }
            } catch (Common::IllegalMoveException errori) {
                infobox_->printInfo(errori.msg() + "!");
            }

            // Valitaan liikutettava actor
        } else if ( hexi->getActors().size() != 0) {
            if (hexi->getActors().at(0)->getActorType() == spinnerResult_.first) {
                highlightedActor_ = (hexi->getActors()).at(0);
                highlightedHex_ = hexi;
            } else {
                infobox_->printInfo("Wrong animal clicked");
            }
            //valitaan liikutettava delfiini
        } else if (hexi->getTransports().size() != 0)  {
            if (hexi->getTransports().at(0)->getTransportType() == spinnerResult_.first) {
                if (hexi->getTransports().at(0)->canMove(statePTR_->currentPlayer())) {
                    highlightedTransport_ = (hexi->getTransports()).at(0);
                    highlightedHex_ = hexi;
                } else {
                    infobox_->printInfo("Can't move dolphin that is carrying other player's pawn");
                }

            } else {
                infobox_->printInfo("Wrong animal clicked");
            }
        }

    }

}

void MainWindow::handle_spinButton()
{
    if (statePTR_->currentGamePhase() == Common::GamePhase::SPINNING && wheelSpinned_ == false) {
        std::pair<std::string,std::string> tulos = runner_->spinWheel();
        ui->spinvaluelabel->setText(QString::fromStdString(tulos.first) + " " + QString::fromStdString(tulos.second));
        wheel_->setPicture(tulos);
        ui->wheellabel->setPixmap(wheel_->pixmap());
        spinnerResult_ = tulos;
        if (boardPTR_->checkAnimalTypeExists(tulos.first)) {
            if (spinnerResult_.second != "D") {
                animalMovesLeft_ = stoi(spinnerResult_.second);
            } else {
                animalMovesLeft_ = -99;
            }
            wheelSpinned_ = true;
            ui->spinButton->setText("Skip actor movement");
            scene1_->update();
        } else {
            infobox_->printInfo("No animal of this type on board");
            change_player();

            ui->playervaluelabel->setText(QString::fromStdString(std::to_string((statePTR_->currentPlayer()))));
            statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
            ui->spinButton->setEnabled(false);
            ui->gamephasevaluelabel->setText("MOVEMENT");
            updateTransportInfo();
        }

        //Tässä tapauksessa pyörää on pyöritetty, ja suoritetaan "Skip actor movement" toiminnallisuus
    } else if (statePTR_->currentGamePhase() == Common::GamePhase::SPINNING && wheelSpinned_ == true) {
        highlightedTransport_ = nullptr;
        highlightedActor_ = nullptr;
        highlightedHex_ = nullptr;
        wheelSpinned_ = false;
        change_player();

        ui->playervaluelabel->setText(QString::fromStdString(std::to_string((statePTR_->currentPlayer()))));
        statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);
        ui->gamephasevaluelabel->setText("MOVEMENT");
        ui->spinButton->setEnabled(false);
        ui->spinButton->setText("SPIN!");
        scene1_->update();
        updateTransportInfo();
    }
}

void MainWindow::end_game() {

    if ( statePTR_->get_availablePlayers().size() == 1 ) {
        boardPTR_->calculateEndOfGamePoints(statePTR_->get_availablePlayers().at(0));
    }

    ResultDialog Loppudialogi;
    Loppudialogi.set_info(boardPTR_->get_PointMap(), playerVector_);
    Loppudialogi.exec();
    MainWindow::close();

}



void MainWindow::change_player(){
    // Ennen isAnyoneAlive checkiä poistetaan pelaaja, jos spinning tai sinking vaiheessa hänen nappulansa ovat kuolleet.
    if ( boardPTR_->playerHasPawns((*playerIter)->getPlayerId()) == false ) {
        statePTR_->removePlayer((*playerIter)->getPlayerId());
    }

    if ( statePTR_->isAnyoneAlive() == false ) {
        //END GAME, REIMPLEMENT
        end_game();

    } else {
        ++playerIter;
        if ( playerIter == playerVector_.end() ) {
            playerIter = playerVector_.begin();
        }
        if (boardPTR_->playerHasPawns((*playerIter)->getPlayerId())) {
            statePTR_->changePlayerTurn((*playerIter)->getPlayerId());
            (*playerIter)->setActionsLeft(3);
             infobox_->printInfo("Changing turn... \nNext player: " + std::to_string(statePTR_->currentPlayer()));
        } else { //player has no pawns, call this function again.
            infobox_->printInfo( "PLAYER HAS NO MORE PAWNS. ID: " + std::to_string((*playerIter)->getPlayerId()));
            statePTR_->removePlayer((*playerIter)->getPlayerId());
            change_player();
        }
    }
}

void MainWindow::handle_boardingButton()
{

    int current_player = statePTR_->currentPlayer();
    int basePawnID = current_player - 1000;
    basePawnID *= 10;
    int pawn = basePawnID + 1;

    if ( ui->Pawn1BoardButton->text() == "Board") {
        if ( boardPTR_->addPawnToTransport(pawn) ) {
            ui->Pawn1BoardButton->setText("Unboard");
        }
    } else {
        if ( boardPTR_->removePawnFromTransport(pawn) ) {
            ui->Pawn1BoardButton->setText("Board");
        }
    }

}

void MainWindow::handle_boardingButton2()
{
    int current_player = statePTR_->currentPlayer();
    int basePawnID = current_player - 1000;
    basePawnID *= 10;
    int pawn = basePawnID + 2;

    if ( ui->Pawn2BoardButton->text() == "Board") {
        if ( boardPTR_->addPawnToTransport(pawn) ) {
            ui->Pawn2BoardButton->setText("Unboard");
        }
    } else {
        if ( boardPTR_->removePawnFromTransport(pawn) ) {
            ui->Pawn2BoardButton->setText("Board");
        }
    }
}

void MainWindow::handle_boardingButton3()
{
    int current_player = statePTR_->currentPlayer();
    int basePawnID = current_player - 1000;
    basePawnID *= 10;
    int pawn = basePawnID + 3;

    if ( ui->Pawn3BoardButton->text() == "Board") {
        if ( boardPTR_->addPawnToTransport(pawn) ) {
            ui->Pawn3BoardButton->setText("Unboard");
        }
    } else {
        if ( boardPTR_->removePawnFromTransport(pawn) ) {
            ui->Pawn3BoardButton->setText("Board");
        }
    }
}

bool MainWindow::allPawnsSwimming()
{
    std::map<int,std::shared_ptr<Common::Pawn>> pawnMap = boardPTR_->get_pawns();
    int playerID = statePTR_->currentPlayer();
    for (auto const& it : pawnMap ) {
        std::shared_ptr<Common::Pawn> pawni = it.second;
        if (pawni->getPlayerId() == playerID) {
            std::shared_ptr<Common::Hex> pawnHex = boardPTR_->get_hexPointers().at(pawni->getCoordinates());
            if ( pawnHex->getPieceType() != "Water" ) {
                return false; // Ainakin yksi pawni on maalla
            } else if (boardPTR_->pawnInTransport(pawni)){
                return false; // Ainakin yksi pawni on transportin kyydissä
            }
        }
       }
        // for loop mennyt loppuun, joten kaikki pawnit vedessä
    return true;
}

void MainWindow::updateTransportInfo()
{
    std::map<std::shared_ptr<Common::Pawn>,bool> TransportInfo = boardPTR_->pawns_NearOrIn_Transport(statePTR_->currentPlayer());
    int current_player = statePTR_->currentPlayer();
    int pawnBaseID = current_player - 1000;
    pawnBaseID *= 10;

    // These bools track whether pawns have been found in the "TransportInfo" map
    bool pawn1 = false;
    bool pawn2 = false;
    bool pawn3 = false;

    for ( auto const& it : TransportInfo ) {
        std::shared_ptr<Common::Pawn> pawn = it.first;
        if (pawn->getId() == pawnBaseID + 1) {
            pawn1 = true;
            ui->Pawn1BoardButton->show();
            if ( it.second == false ) {
                ui->Pawn1BoardButton->setText("Board");     //Pawn in a hex with transport, display option "Board"
            } else {
                ui->Pawn1BoardButton->setText("Unboard");   //Pawn inside a transport, display option "Unboard"
            }
        } else if (pawn->getId() == pawnBaseID + 2) {
            pawn2 = true;
            ui->Pawn2BoardButton->show();
            if ( it.second == false ) {
                ui->Pawn2BoardButton->setText("Board");
            } else {
                ui->Pawn2BoardButton->setText("Unboard");
            }
        } else if (pawn->getId() == pawnBaseID + 3) {
            pawn3 = true;
            ui->Pawn3BoardButton->show();
            if ( it.second == false ) {
                ui->Pawn3BoardButton->setText("Board");
            } else {
                ui->Pawn3BoardButton->setText("Unboard");
            }
        }
    }

    // Hide buttons, if pawns not found in map.
    if ( pawn1 == false ) {
        ui->Pawn1BoardButton->hide();
    }

    if ( pawn2 == false ) {
        ui->Pawn2BoardButton->hide();
    }

    if ( pawn3 == false ) {
        ui->Pawn3BoardButton->hide();
    }
}

void MainWindow::handle_startButton()
{
    delete startButton_;
    statePTR_->changePlayerTurn((*playerIter)->getPlayerId());
    (*playerIter)->setActionsLeft(3);
    statePTR_->changeGamePhase(Common::GamePhase::MOVEMENT);

}

unsigned int MainWindow::cubeCoordinateDistance(Common::CubeCoordinate source, Common::CubeCoordinate target) const
{

    return ((abs(source.x - target.x) + abs(source.y - target.y)
             + abs(source.z - target.z)) / 2);

}




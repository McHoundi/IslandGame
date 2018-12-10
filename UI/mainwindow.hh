#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include "gameboard.hh"
#include <memory>
#include "player.hh"
#include "igameboard.hh"
#include "gameengine.hh"
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QShowEvent>
#include "iostream"
#include "QDebug"
#include "startdialog.hh"
#include "QGraphicsPixmapItem"
#include "QGraphicsEllipseItem"
#include "pixmapgraphics.hh"
#include "wheel.hh"
#include "QPushButton"
#include "infobox.hh"


#include "vector"

#include "gamestate.hh"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	
	//draw_map piirtää kartan, ajetaan kun ollaan alustettu lauta.
    void draw_map();
	
	// get_inputs Tallettaa aloitusikkunassa määritettyjä arvoja.
    void get_inputs(int playerCount);

	
	//Initialize_players luo aloitusikkunassa määritetyn määrän pelaajia.

    std::vector<std::shared_ptr<Common::IPlayer>> initialize_players();
    void initialize_pawns(std::shared_ptr<Common::IPlayer> pelaaja);
    void run_game();
    // Alustaa pelin runnerin
    void initialize_runner();



    ~MainWindow();

public slots:
    // slotit eri nappien painalluksille
    void hex_chosen(std::shared_ptr<Common::Hex> hexi);

    void handle_startButton();

    void handle_spinButton();

    void handle_boardingButton();
    void handle_boardingButton2();
    void handle_boardingButton3();


private:
    bool allPawnsSwimming(); // kertoo ovatko kaikki pawnit vedessä ilman transporttia
    void updateTransportInfo(); // päivittää board/unboard painikkeet
    void change_player(); // vaihtaa pelaajan vuoron seuraavaan

    Ui::MainWindow *ui;
    int playerCount_; //aloitusikkunassa määritetty pelaajien määrä.

    QGraphicsView* view1_;
    QGraphicsScene* scene1_;
    QPushButton* aloitusnappi_;
    std::shared_ptr<Student::GameBoard> boardPTR_; //sharedptr to the gameboard, saved here for convenience purposes
    std::shared_ptr<GameState> statePTR_;
    std::vector<std::shared_ptr<Common::IPlayer> > playerVector_;
    std::map<int,std::shared_ptr<Common::IPlayer> > players_; // map of players, searchable by playerID
    bool wheelSpinned_ = false;
    std::shared_ptr<Common::Hex> highlightedHex_ = nullptr; //valittu ruutu
    std::shared_ptr<Common::Pawn> highlightedPawn_ = nullptr; // valittu nappula
    std::shared_ptr<Common::Actor> highlightedActor_ = nullptr; // valittu actor
    std::shared_ptr<Common::Transport> highlightedTransport_ = nullptr; // valittu transport
    std::shared_ptr<Common::IGameRunner> runner_;
    QPushButton* startButton_;
    infoBox* infobox_; // ui:n laatikko johon tulostetaan pelin kannalta hyödyllistä tietoa

    std::vector<std::shared_ptr<Common::IPlayer>>::iterator playerIter;
    wheel* wheel_; // osoitin wheel itemiin joka toteuttaa visualisoidun kiekon
    std::pair<std::string,std::string> spinnerResult_; // spinWheelin tulos, (eläin, arvo)
    int animalMovesLeft_;

    // laskee kahden pisteen välisen etäisyyden ruuduissa
    unsigned int cubeCoordinateDistance(Common::CubeCoordinate source, Common::CubeCoordinate target) const;
    void end_game();
};

#endif // MAINWINDOW_HH

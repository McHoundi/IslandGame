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
#include "iostream"
#include "QDebug"
#include "startdialog.hh"
#include "QGraphicsPixmapItem"
#include "QGraphicsEllipseItem"
#include "pixmapgraphics.hh"

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
    void run_movement_phase();

    ~MainWindow();

public slots:
    void hex_chosen(std::shared_ptr<Common::Hex> hexi);

private:
    Ui::MainWindow *ui;
    int playerCount_; //aloitusikkunassa määritetty pelaajien määrä.

    QGraphicsView* view1_;
    QGraphicsScene* scene1_;
    std::shared_ptr<Student::GameBoard> boardPTR_; //sharedptr to the gameboard, saved here for convenience purposes
    std::shared_ptr<GameState> statePTR_;
    std::vector<std::shared_ptr<Common::IPlayer> > playerVector_;
    bool hexIsHighlighted_ = false;
    std::shared_ptr<Common::Hex> highlightedHex_ = nullptr;
    std::shared_ptr<Common::Pawn> highlightedPawn_ = nullptr;
    std::shared_ptr<Common::IGameRunner> runner_;

};

#endif // MAINWINDOW_HH

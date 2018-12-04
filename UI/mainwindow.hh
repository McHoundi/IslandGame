#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include "gameboard.hh"
#include <memory>
#include "player.hh"
#include "igameboard.hh"
#include "gameengine.hh"
#include "gamestate.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void draw_map(std::shared_ptr<Student::GameBoard> lautaptr, QGraphicsScene *scene);
    void get_inputs(int playerCount);
    std::vector<std::shared_ptr<Common::IPlayer>> initialize_players();
    ~MainWindow();

public slots:
    void hex_chosen(std::shared_ptr<Common::Hex> hexi);

private:
    Ui::MainWindow *ui;
    QGraphicsView* view_;
    int playerCount_;
    std::shared_ptr<Student::GameBoard> boardPTR_;
    std::shared_ptr<GameState> statePTR_;
    bool hexIsHighlighted_ = false;
    std::shared_ptr<Common::Hex> highlightedHex_;
    std::map<Common::CubeCoordinate, hexgraphics*> hexes_;
};

#endif // MAINWINDOW_HH

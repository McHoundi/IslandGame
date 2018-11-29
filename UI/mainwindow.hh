#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include "gameboard.hh"
#include <memory>
#include "player.hh"
#include "igameboard.hh"
#include "gameengine.hh"

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView* view_;
    int playerCount_;
};

#endif // MAINWINDOW_HH

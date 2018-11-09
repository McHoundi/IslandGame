#include "mainwindow.hh"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QLayout>
#include <QWidget>
// #include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include "hexagon.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsItem* item = new QGraphicsSimpleTextItem("Käytännössä \n koordinaattijärjestelmiä on kolme eli jokaiselle \n osalle omansa. Käytössä on siten: elementtikoordinaatit, maisemakoordinaatit, näkymäkoordinaatit. Näkymäkoordinaatit ovat QGraphicsView:n koordinaatteja. Maisemakoordinaatit ovat maiseman sisällä olevien elementtien paikan määrittäviä koordinaatteja. Jokaiselle elementillä on myös omat koordinaattinsa, jossa 0,0 sijaitsee keskellä elementtiä. Elementtikoordinaateilla on merkitystä omia elementtejä luotaessa, sillä esimerkiksi hiiren klikkaustapahtumien sijainti määritellään niiden avulla. Myös elementin ulkoreunan määräävä suorakaide ja muoto määritellään elementtikoordinaateilla.");
    Hexagon* hexagoni = new Hexagon;
    scene->addItem(hexagoni);

    ui->graphicsView->setScene(scene);

    /*
    QGraphicsView* view_ = new QGraphicsView(this);
    view_->setScene(scene);
    scene->setSceneRect(0, 0, 200, 200);
    */
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

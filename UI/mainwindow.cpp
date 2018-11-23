#include "mainwindow.hh"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QLayout>
#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include "hexagon2.hh"
#include "hexagon.hh"
#include "kartta.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;

    kartta meidan_kartta;
    meidan_kartta.build_map(scene);

    //Hexagon* hexagoni = new Hexagon;
    //scene->addItem(hexagoni);

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

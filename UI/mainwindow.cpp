#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLayout>
#include <QWidget>
// #include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsItem* item = new QGraphicsSimpleTextItem("hei!");
    scene->addItem(item);

    QGraphicsView* view_ = new QGraphicsView(this);
    view_->setScene(scene);
    scene->setSceneRect(-30, 0, 200, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

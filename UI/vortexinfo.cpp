#include "vortexinfo.hh"
#include "ui_vortexinfo.h"

vortexinfo::vortexinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vortexinfo)
{
    ui->setupUi(this);
}

vortexinfo::~vortexinfo()
{
    delete ui;
}

#include "startdialog.hh"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::accept()
{
    emit runClicked(ui->PlayersSpinbox->value());
    QDialog::accept();
}

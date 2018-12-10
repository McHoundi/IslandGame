#ifndef RESULTDIALOG_HH
#define RESULTDIALOG_HH

#include <QDialog>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);
    ~ResultDialog();

private:
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_HH

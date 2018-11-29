#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_HH

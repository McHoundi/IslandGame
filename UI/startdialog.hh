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

public slots:
    virtual void accept();

signals:
    void runClicked(int playerCount);

private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_HH

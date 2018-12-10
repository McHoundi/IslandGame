#ifndef RESULTDIALOG_HH
#define RESULTDIALOG_HH

#include <QDialog>
#include "player.hh"

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);

    ~ResultDialog();

    void set_info(std::map<int, int> pointMap, std::vector<std::shared_ptr<Common::IPlayer> > playervect);

signals:
    void CloseClicked();

private:
    std::map<int,int> playerPoints_;
    std::vector<std::shared_ptr<Common::IPlayer>> playerVector_;
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_HH

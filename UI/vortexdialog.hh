#ifndef VORTEXDIALOG_HH
#define VORTEXDIALOG_HH

#include <QDialog>

namespace Ui {
class VortexDialog;
}

class VortexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VortexDialog(QWidget *parent = 0);
    ~VortexDialog();

private:
    Ui::VortexDialog *ui;
};

#endif // VORTEXDIALOG_HH

#ifndef VORTEXINFO_HH
#define VORTEXINFO_HH

#include <QDialog>

namespace Ui {
class vortexinfo;
}

class vortexinfo : public QDialog
{
    Q_OBJECT

public:
    explicit vortexinfo(QWidget *parent = 0);
    ~vortexinfo();

private:
    Ui::vortexinfo *ui;
};

#endif // VORTEXINFO_HH

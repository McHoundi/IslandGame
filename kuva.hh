#ifndef KUVA_HH
#define KUVA_HH

#include <QObject>

class kuva : public QObject
{
    Q_OBJECT
public:
    explicit kuva(QObject *parent = nullptr);

signals:

public slots:
};

#endif // KUVA_HH
#ifndef System_H
#define System_H

#include <QObject>

class System : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)

public:
    System(QObject* parent = nullptr);

    QString qtVersion() const;

};

#endif

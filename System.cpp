#include "System.h"

System::System(QObject * parent) :
    QObject(parent)
{
}

QString System::qtVersion() const
{
    return qVersion();
}

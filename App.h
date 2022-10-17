#ifndef App_H
#define App_H

#include <QObject>
#include <QUrl>

class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl href READ href CONSTANT)

public:
    App(QObject* parent = nullptr);

protected:
    QUrl href() const;

};

#endif

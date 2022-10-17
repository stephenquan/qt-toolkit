#ifndef Engine_H
#define Engine_H

#include <QObject>
#include <QVariant>
#include <QStringList>

class Engine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList allSelectors READ allSelectors NOTIFY selectorsChanged)

public:
    Engine(QObject* parent = nullptr);
    ~Engine();

    Q_INVOKABLE void clearComponentCache();

    QStringList allSelectors();

signals:
    void selectorsChanged();

};

#endif

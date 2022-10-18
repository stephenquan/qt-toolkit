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
    Q_INVOKABLE QString stringCompress(const QString& str);
    Q_INVOKABLE QString stringUncompress(const QString& str);

    QStringList allSelectors();

signals:
    void selectorsChanged();

};

#endif

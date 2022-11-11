#ifndef App_H
#define App_H

#include <QObject>
#include <QUrl>
#include <QClipboard>
#include <QVariant>

class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl href READ href CONSTANT)

public:
    App(QObject* parent = nullptr);

    Q_INVOKABLE void copy(const QVariant& data);

protected:
    QUrl href() const;

    QClipboard* m_Clipboard;

};

#endif

#ifndef System_H
#define System_H

#include <QObject>

class UrlInfo;

class System : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)

public:
    System(QObject* parent = nullptr);

    QString qtVersion() const;
    Q_INVOKABLE QString stringCompress(const QString& str);
    Q_INVOKABLE QString stringUncompress(const QString& str);
    Q_INVOKABLE UrlInfo* urlInfo(const QUrl& url);

};

#endif

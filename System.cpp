#include "System.h"
#include "UrlInfo.h"

System::System(QObject * parent) :
    QObject(parent)
{
}

QString System::qtVersion() const
{
    return qVersion();
}

QString System::stringCompress(const QString& str)
{
    return QString::fromUtf8(qCompress(str.toUtf8()).toBase64());
}

QString System::stringUncompress(const QString& str)
{
    return QString::fromUtf8(qUncompress(QByteArray::fromBase64(str.toUtf8())));
}

UrlInfo* System::urlInfo(const QUrl& url)
{
    return UrlInfo::newUrlInfo(url);
}

#include "System.h"
#include "UrlInfo.h"
#include "ImageBuffer.h"

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

ImageBuffer* System::image(const QVariant& image)
{
    return ImageBuffer::newImageBuffer(image);
}

QByteArray System::btoh(const QByteArray& data)
{
    return data.toHex();
}

QByteArray System::htob(const QByteArray& hex)
{
    return QByteArray::fromHex(hex);
}

QByteArray System::hash(const QByteArray& data, Algorithm algorithm)
{
    return QCryptographicHash::hash(data, static_cast<QCryptographicHash::Algorithm>(static_cast<int>(algorithm))).toHex();
}


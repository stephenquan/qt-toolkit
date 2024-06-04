#include "System.h"
#include "UrlInfo.h"
#include "ImageBuffer.h"
#include <QMetaEnum>

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

QStringList System::enumerators(const QVariant& obj) const
{
    QObject* _obj = qvariant_cast<QObject*>(obj);
    if (!_obj) return QStringList();
    const QMetaObject* mo = _obj->metaObject();
    if (!mo) return QStringList();
    QStringList list;
    for (int i = 0; i < mo->enumeratorCount(); i++)
    {
        QMetaEnum e = mo->enumerator(i);
        list.append(QString::fromUtf8(e.name()));
    }
    return list;
}

QVariant System::enumerator(const QVariant& obj, const QString& name) const
{
    QObject* _obj = qvariant_cast<QObject*>(obj);
    if (!_obj) return QVariant();
    const QMetaObject* mo = _obj->metaObject();
    if (!mo) return QVariant();
    int i = mo->indexOfEnumerator(name.toUtf8());
    if (i == -1) return QVariant();
    QMetaEnum e = mo->enumerator(i);
    QVariantList list;
    for (int j = 0; j < e.keyCount(); j++)
    {
        QVariantMap m;
        m["key"] = QString::fromUtf8(e.key(j));
        m["value"] = e.value(j);
        list.append(m);
    }
    return list;
}

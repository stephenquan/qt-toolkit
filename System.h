#ifndef System_H
#define System_H

#include <QObject>
#include <QCryptographicHash>

class UrlInfo;
class ImageBuffer;

class System : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)

public:
    enum Algorithm {
        Md4 = QCryptographicHash::Md4,
        Md5 = QCryptographicHash::Md5,
        Sha1 = QCryptographicHash::Sha1,
        Sha224 = QCryptographicHash::Sha224,
        Sha256 = QCryptographicHash::Sha256,
        Sha384 = QCryptographicHash::Sha384,
        Sha512 = QCryptographicHash::Sha512,
        Sha3_224 = QCryptographicHash::Sha3_224,
        Sha3_256 = QCryptographicHash::Sha3_256,
        Sha3_384 = QCryptographicHash::Sha3_384,
        Sha3_512 = QCryptographicHash::Sha3_512,
        Keccak_224 = QCryptographicHash::Keccak_224,
        Keccak_256 = QCryptographicHash::Keccak_256,
        Keccak_384 = QCryptographicHash::Keccak_384,
        Keccak_512 = QCryptographicHash::Keccak_512
    };
    Q_ENUM(Algorithm)

public:
    System(QObject* parent = nullptr);


    QString qtVersion() const;
    Q_INVOKABLE QString stringCompress(const QString& str);
    Q_INVOKABLE QString stringUncompress(const QString& str);
    Q_INVOKABLE QByteArray btoh(const QByteArray& data);
    Q_INVOKABLE QByteArray htob(const QByteArray& hex);
    Q_INVOKABLE QByteArray hash(const QByteArray& data, Algorithm algorithm = Algorithm::Md5);
    Q_INVOKABLE UrlInfo* urlInfo(const QUrl& url);
    Q_INVOKABLE ImageBuffer* image(const QVariant& image);
    Q_INVOKABLE QStringList enumerators(const QVariant& obj) const;
    Q_INVOKABLE QVariant enumerator(const QVariant& obj, const QString& name) const;

};

#endif

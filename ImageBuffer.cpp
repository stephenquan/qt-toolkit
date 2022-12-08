#include <QBuffer>
#include <QQmlEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "ImageBuffer.h"

ImageBuffer::ImageBuffer(QObject * parent) :
    QObject(parent)
{
}

ImageBuffer* ImageBuffer::newImageBuffer(const QVariant& image, QJSEngine::ObjectOwnership objectOwnership)
{
    ImageBuffer* imageBuffer = new ImageBuffer();
    imageBuffer->setImage(image);
    QJSEngine::setObjectOwnership(imageBuffer, objectOwnership);
    return imageBuffer;
}

void ImageBuffer::setImage(const QVariant& image)
{
    m_Image = image.value<QImage>();
}

QUrl ImageBuffer::toDataURL(const QString& format, const QVariant& options) const
{
    Q_UNUSED(format)
    Q_UNUSED(options)
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    m_Image.save(&buffer, "PNG", -1);
    return QString("data:image/png;base64,") + data.toBase64();
}

void ImageBuffer::setUrl(const QUrl& url)
{
    if (!url.isValid())
    {
        emit error(QString("Invalid URL"));
        return;
    }

    if (url.isLocalFile())
    {
        setFilePath(url.toLocalFile());
        return;
    }

    _setUrl(url);
    _setFilePath(QString());

    QQmlEngine* engine = qmlEngine(this);
    if (!engine)
    {
        emit error(QString("No engine"));
        return;
    }

    QNetworkAccessManager* manager = engine->networkAccessManager();
    if (!manager)
    {
        emit error(QString("No QNetworkAccessManager"));
        return;
    }

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ImageBuffer::onFinished);
}

void ImageBuffer::setFilePath(const QString& filePath)
{
    _setUrl(QUrl::fromLocalFile(filePath));
    _setFilePath(filePath);

    if (!m_Image.load(filePath))
    {
        emit error(QString("Cannot load from file"));
        return;
    }

    emit imageChanged();
    emit loaded();
}

void ImageBuffer::onFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
    {
        return;
    }

    QByteArray buffer = reply->readAll();
    if (!m_Image.loadFromData(buffer))
    {
        emit error(QString("Cannot load"));
        return;
    }

    emit imageChanged();
    emit loaded();
}

void ImageBuffer::_setUrl(const QUrl& url)
{
    if (m_Url == url)
    {
        return;
    }

    m_Url = url;

    emit urlChanged();
}

void ImageBuffer::_setFilePath(const QString& filePath)
{
    if (m_FilePath == filePath)
    {
        return;
    }

    m_FilePath = filePath;

    emit filePathChanged();
}

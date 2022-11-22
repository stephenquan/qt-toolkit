#include <QBuffer>
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


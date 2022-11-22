#ifndef ImageBuffer_H
#define ImageBuffer_H

#include <QObject>
#include <QUrl>
#include <QImage>
#include <QJSEngine>

class ImageBuffer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int width READ width NOTIFY imageChanged)
    Q_PROPERTY(int height READ height NOTIFY imageChanged)

public:
    ImageBuffer(QObject* parent = nullptr);

    static ImageBuffer* newImageBuffer(const QVariant& image, QJSEngine::ObjectOwnership objectOwnership = QJSEngine::JavaScriptOwnership);

    Q_INVOKABLE QUrl toDataURL(const QString& format = QString(), const QVariant& options = QVariant()) const;

    int width() const { return m_Image.width(); }
    int height() const { return m_Image.height(); }

    QVariant image() const { return m_Image; }
    void setImage(const QVariant& image);

signals:
    void imageChanged();

protected:
    QImage m_Image;

};

#endif

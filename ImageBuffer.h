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
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)

public:
    ImageBuffer(QObject* parent = nullptr);

    static ImageBuffer* newImageBuffer(const QVariant& image, QJSEngine::ObjectOwnership objectOwnership = QJSEngine::JavaScriptOwnership);

    QUrl url() const { return m_Url; }
    void setUrl(const QUrl& url);

    QString filePath() const { return m_FilePath; }
    void setFilePath(const QString& filePath);

    Q_INVOKABLE QUrl toDataURL(const QString& format = QString(), const QVariant& options = QVariant()) const;

    int width() const { return m_Image.width(); }
    int height() const { return m_Image.height(); }

    QVariant image() const { return m_Image; }
    void setImage(const QVariant& image);

signals:
    void filePathChanged();
    void imageChanged();
    void urlChanged();
    void loaded();
    void error(const QString& errorString);

protected slots:
    void onFinished();

protected:
    QImage m_Image;
    QUrl m_Url;
    QString m_FilePath;

    void _setUrl(const QUrl& url);
    void _setFilePath(const QString& filePath);

};

#endif

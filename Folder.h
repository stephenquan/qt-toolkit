#ifndef Folder_H
#define Folder_H

#include <QObject>
#include <QVariantMap>
#include <QUrl>
#include <QDir>

class Folder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY pathChanged)

public:
    Folder(QObject* parent = nullptr);

    static Folder* newFolder(const QString& path);
    static Folder* newFolder(const QUrl& url);

    QString path() const;
    void setPath(const QString& path);

    QUrl url() const;
    void setUrl(const QUrl& url);

    Q_INVOKABLE QString filePath(const QString& fileName) const;
    Q_INVOKABLE QUrl fileUrl(const QString& fileName) const;
    Q_INVOKABLE bool writeTextFile(const QString& fileName, const QString& text);

signals:
    void pathChanged();

protected:
    QDir m_dir;

};

#endif

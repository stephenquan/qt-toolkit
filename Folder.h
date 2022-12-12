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
    Q_PROPERTY(bool exists READ exists NOTIFY existsChanged)

public:
    Folder(QObject* parent = nullptr);

    static Folder* newFolder(const QString& path);
    static Folder* newFolder(const QUrl& url);

    bool exists() const { return m_dir.exists(); }

    QString path() const;
    void setPath(const QString& path);

    QUrl url() const;
    void setUrl(const QUrl& url);

    Q_INVOKABLE Folder* folder(const QString& subdir) const;

    Q_INVOKABLE QString filePath(const QString& fileName) const;
    Q_INVOKABLE QUrl fileUrl(const QString& fileName) const;
    Q_INVOKABLE bool writeTextFile(const QString& fileName, const QString& text);
    Q_INVOKABLE bool writeFile(const QString& fileName, const QByteArray& data);

    Q_INVOKABLE bool mkpath();

signals:
    void existsChanged();
    void pathChanged();

protected:
    QDir m_dir;

};

#endif

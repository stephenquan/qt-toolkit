#include "Folder.h"
#include <QUrl>
#include <QQmlEngine>
#include <QDebug>

Folder::Folder(QObject * parent) :
    QObject(parent)
{
}

Folder* Folder::newFolder(const QString& path)
{
    Folder* folder = new Folder();
    if (!path.isEmpty())
    {
        folder->setPath(path);
    }
    QQmlEngine::setObjectOwnership(folder, QQmlEngine::JavaScriptOwnership);
    return folder;
}

Folder* Folder::newFolder(const QUrl& url)
{
    Folder* folder = new Folder();
    folder->setUrl(url);
    QQmlEngine::setObjectOwnership(folder, QQmlEngine::JavaScriptOwnership);
    return folder;
}

QString Folder::path() const
{
    return m_dir.absolutePath();
}

void Folder::setPath(const QString& path)
{
    QString oldPath = m_dir.absolutePath();
    m_dir.setPath(path);
    if (oldPath == m_dir.absolutePath())
    {
        return;
    }
    emit pathChanged();
    emit existsChanged();
}

QUrl Folder::url() const
{
    return QUrl::fromLocalFile(path());
}

void Folder::setUrl(const QUrl& url)
{
    setPath(url.toLocalFile());
}

bool Folder::writeTextFile(const QString& fileName, const QString& text)
{
    return writeFile(fileName, text.toUtf8());
}

bool Folder::writeFile(const QString& fileName, const QByteArray& data)
{
    QFile file(filePath(fileName));
    bool ok = file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if (!ok)
    {
        return ok;
    }
    file.write(data);
    file.close();
    return true;
}

QString Folder::filePath(const QString& fileName) const
{
    return QDir::cleanPath(m_dir.absoluteFilePath(fileName));
}

QUrl Folder::fileUrl(const QString& fileName) const
{
    return QUrl::fromLocalFile(filePath(fileName));
}

Folder* Folder::folder(const QString& subdir) const
{
    return newFolder(path() + "/" + subdir);
}

bool Folder::mkpath()
{
    if (exists())
    {
        return true;
    }

    bool result = QDir().mkpath(m_dir.absolutePath());
    if (exists())
    {
        emit existsChanged();
    }
    return result;
}

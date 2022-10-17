#include "FileSystem.h"
#include "Folder.h"
#include <QUrl>
#include <QQmlEngine>

FileSystem::FileSystem(QObject * parent) :
    QObject(parent),
    m_homeFolder(nullptr),
    m_tempFolder(nullptr),
    m_documentsFolder(nullptr),
    m_picturesFolder(nullptr)
{
}

Folder* FileSystem::homeFolder()
{
    if (m_homeFolder)
    {
        return m_homeFolder;
    }

    QString folderPath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::HomeLocation);
    m_homeFolder = new Folder(this);
    m_homeFolder->setPath(folderPath);
    return m_homeFolder;
}

Folder* FileSystem::tempFolder()
{
    if (m_tempFolder)
    {
        return m_tempFolder;
    }

    QString folderPath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::TempLocation);
    m_tempFolder = new Folder(this);
    m_tempFolder->setPath(folderPath);
    return m_tempFolder;
}

Folder* FileSystem::documentsFolder()
{
    if (m_documentsFolder)
    {
        return m_documentsFolder;
    }

    QString folderPath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation);
    m_documentsFolder = new Folder(this);
    m_documentsFolder->setPath(folderPath);
    return m_documentsFolder;
}

Folder* FileSystem::picturesFolder()
{
    if (m_picturesFolder)
    {
        return m_picturesFolder;
    }

    QString folderPath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::PicturesLocation);
    m_picturesFolder = new Folder(this);
    m_picturesFolder->setPath(folderPath);
    return m_picturesFolder;
}

Folder* FileSystem::standardFolder(FileSystem::StandardLocation location) const
{
    QString folderPath = QStandardPaths::writableLocation(static_cast<QStandardPaths::StandardLocation>(location));
    return Folder::newFolder(folderPath);
}


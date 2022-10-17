#ifndef FileSystem_H
#define FileSystem_H

#include <QObject>
#include <QStandardPaths>
#include "Folder.h"

class FileSystem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Folder* homeFolder READ homeFolder CONSTANT)
    Q_PROPERTY(Folder* tempFolder READ tempFolder CONSTANT)
    Q_PROPERTY(Folder* documentsFolder READ documentsFolder CONSTANT)
    Q_PROPERTY(Folder* picturesFolder READ picturesFolder CONSTANT)

public:
    enum StandardLocation
    {
        DesktopLocation = QStandardPaths::DesktopLocation,
        DocumentsLocation = QStandardPaths::DocumentsLocation,
        FontsLocation = QStandardPaths::FontsLocation,
        ApplicationsLocation = QStandardPaths::ApplicationsLocation,
        MusicLocation = QStandardPaths::MusicLocation,
        MoviesLocation = QStandardPaths::MoviesLocation,
        PicturesLocation = QStandardPaths::PicturesLocation,
        TempLocation = QStandardPaths::TempLocation,
        HomeLocation = QStandardPaths::HomeLocation,
        AppLocalDataLocation = QStandardPaths::AppLocalDataLocation,
        CacheLocation = QStandardPaths::CacheLocation,
        GenericDataLocation = QStandardPaths::GenericDataLocation,
        RuntimeLocation = QStandardPaths::RuntimeLocation,
        ConfigLocation = QStandardPaths::ConfigLocation,
        DownloadLocation = QStandardPaths::DownloadLocation,
        GenericCacheLocation = QStandardPaths::GenericCacheLocation,
        GenericConfigLocation = QStandardPaths::GenericConfigLocation,
        AppDataLocation = QStandardPaths::AppDataLocation,
        AppConfigLocation = QStandardPaths::AppConfigLocation,
        PublicShareLocation = QStandardPaths::PublicShareLocation,
        TemplatesLocation = QStandardPaths::TemplatesLocation
    };

    Q_ENUMS(StandardLocation)

public:
    FileSystem(QObject* parent = nullptr);

    Folder* homeFolder();
    Folder* tempFolder();
    Folder* documentsFolder();
    Folder* picturesFolder();

    Q_INVOKABLE Folder* standardFolder(FileSystem::StandardLocation location) const;

signals:

protected:
    Folder* m_homeFolder;
    Folder* m_tempFolder;
    Folder* m_documentsFolder;
    Folder* m_picturesFolder;

};

#endif

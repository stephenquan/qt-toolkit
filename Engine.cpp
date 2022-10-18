#include "Engine.h"
#include <QUrl>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QFileSelector>

Engine::Engine(QObject * parent) :
    QObject(parent)
{
}

Engine::~Engine()
{
}

void Engine::clearComponentCache()
{
    qmlEngine(this)->clearComponentCache();
}

QString Engine::stringCompress(const QString& str)
{
    return QString::fromUtf8(qCompress(str.toUtf8()).toBase64());
}

QString Engine::stringUncompress(const QString& str)
{
    return QString::fromUtf8(qUncompress(QByteArray::fromBase64(str.toUtf8())));
}

QStringList Engine::allSelectors()
{
    return QQmlFileSelector(qmlEngine(this)).selector()->allSelectors();
}


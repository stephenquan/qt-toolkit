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

QStringList Engine::allSelectors()
{
    return QQmlFileSelector(qmlEngine(this)).selector()->allSelectors();
}


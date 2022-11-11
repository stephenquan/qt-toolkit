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

void Engine::clearSingletons()
{
    qmlEngine(this)->clearSingletons();
}

void Engine::trimComponentCache()
{
    qmlEngine(this)->trimComponentCache();
}

QStringList Engine::allSelectors()
{
    return QQmlFileSelector(qmlEngine(this)).selector()->allSelectors();
}


#include "App.h"
#include <QUrl>
#include <QQmlEngine>

#ifdef EMSCRIPTEN
#include <emscripten/val.h>
#include <emscripten.h>
#endif

#ifdef EMSCRIPTEN

EMSCRIPTEN_KEEPALIVE
void sayHi()
{
    printf("Hi!\n");
}

#endif

App::App(QObject * parent) :
    QObject(parent)
{
}
QUrl App::href() const
{
#ifdef EMSCRIPTEN
    emscripten::val _location = emscripten::val::global("location");
    return QUrl(QString::fromStdString(_location["href"].as<std::string>()));
#else
    return QUrl();
#endif
}

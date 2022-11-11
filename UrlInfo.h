#ifndef UrlInfo_H
#define UrlInfo_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QJSEngine>

class UrlInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

public:
    UrlInfo(QObject* parent = nullptr);

    static UrlInfo* newUrlInfo(const QUrl& url, QJSEngine::ObjectOwnership objectOwnership = QJSEngine::JavaScriptOwnership);

    QString query() const;

    QUrl url() const;
    void setUrl(const QUrl& url);

    Q_INVOKABLE QVariant queryItem(const QString& key) const;
    Q_INVOKABLE void setQueryItem(const QString& key, const QString& value);

signals:
    void urlChanged();

protected:
    QUrl m_HostPort;
    QUrlQuery m_Query;

};

#endif

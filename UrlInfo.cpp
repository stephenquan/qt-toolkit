#include "UrlInfo.h"

UrlInfo::UrlInfo(QObject * parent) :
    QObject(parent)
{
}

UrlInfo* UrlInfo::newUrlInfo(const QUrl& url, QJSEngine::ObjectOwnership objectOwnership)
{
    UrlInfo* urlInfo = new UrlInfo();
    urlInfo->setUrl(url);
    QJSEngine::setObjectOwnership(urlInfo, objectOwnership);
    return urlInfo;
}

QString UrlInfo::query() const
{
    QStringList queryItems;
    QPair<QString, QString> item;
    foreach (item, m_Query.queryItems(QUrl::FullyDecoded))
    {
        queryItems.append(item.first + "=" + item.second);
    }
    return queryItems.join("&");
}

QUrl UrlInfo::url() const
{
    QString hostPort = m_HostPort.toString();
    QString _query = query();
    return (_query.isEmpty() || _query.isNull())
            ? hostPort
            : hostPort + "?" + _query;
}

void UrlInfo::setUrl(const QUrl& url)
{
    m_HostPort = url;
    m_HostPort.setQuery(QString());
    m_Query = QUrlQuery(url);
    emit urlChanged();
}

QVariant UrlInfo::queryItem(const QString& key) const
{
    return m_Query.queryItemValue(key);
}

void UrlInfo::setQueryItem(const QString& key, const QString& value)
{
    if (value.isEmpty() || value.isNull())
    {
        if (!m_Query.hasQueryItem(key))
        {
            return;
        }
        m_Query.removeQueryItem(key);
        emit urlChanged();
        return;
    }

    if (value == m_Query.queryItemValue(key))
    {
        return;
    }

    if (m_Query.hasQueryItem(key))
    {
        m_Query.removeQueryItem(key);
    }

    m_Query.addQueryItem(key, value);
    emit urlChanged();
}

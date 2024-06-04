#ifndef CustomSyntaxHighlighter_H
#define CustomSyntaxHighlighter_H

#include <QObject>
#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QQuickTextDocument>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QColor>
#include "TextCharFormat.h"

class CustomSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    Q_PROPERTY(QVariant textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(int currentBlockState READ currentBlockState WRITE setCurrentBlockState NOTIFY currentBlockStateChanged)

public:
    CustomSyntaxHighlighter(QObject* parent = nullptr);

    Q_INVOKABLE void setColor(int start, int count, const QColor& color);
    Q_INVOKABLE void setFont(int start, int count, const QFont& font);
    Q_INVOKABLE void setFormat(int start, int count, const QVariant& format);
    Q_INVOKABLE void rehighlight();

signals:
    void textDocumentChanged();
    void currentBlockStateChanged();

    void highlightText(const QString& text);

protected:
    QVariant m_TextDocument;

    int currentBlockState() const;
    void setCurrentBlockState(int blockState);

    QVariant textDocument() const;
    void setTextDocument(const QVariant& textDocument);

    virtual void highlightBlock(const QString& text);

};

#endif

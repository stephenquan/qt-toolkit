#include "CustomSyntaxHighlighter.h"
#include <QQmlEngine>

CustomSyntaxHighlighter::CustomSyntaxHighlighter( QObject* parent ) :
    QSyntaxHighlighter(parent)
{
}

void CustomSyntaxHighlighter::highlightBlock( const QString &text )
{
    emit highlightText(text);
}

QVariant CustomSyntaxHighlighter::textDocument() const
{
    return m_TextDocument;
}

void CustomSyntaxHighlighter::setTextDocument( const QVariant& textDocument )
{
    if (textDocument == m_TextDocument)
    {
        return;
    }

    m_TextDocument = textDocument;

    QQuickTextDocument* qquickTextDocument = qvariant_cast<QQuickTextDocument*>(textDocument);
    if (qquickTextDocument)
    {
        setDocument(qquickTextDocument->textDocument());
    }
    else
    {
        setDocument(nullptr);
    }

    rehighlight();
    emit textDocumentChanged();
}

void CustomSyntaxHighlighter::setColor( int start, int count, const QColor& color)
{
    QSyntaxHighlighter::setFormat( start, count, color );
}

void CustomSyntaxHighlighter::setFont( int start, int count, const QFont& font )
{
    QSyntaxHighlighter::setFormat( start, count, font );
}

void CustomSyntaxHighlighter::setFormat( int start, int count, const QVariant& format )
{
    if ( format.canConvert(QVariant::Color) )
    {
        QSyntaxHighlighter::setFormat( start, count, format.value<QColor>() );
        return;
    }

    TextCharFormat* charFormat = qvariant_cast<TextCharFormat*>( format );
    if ( charFormat )
    {
        QSyntaxHighlighter::setFormat( start, count, *charFormat );
        return;
    }

    if ( format.canConvert(QVariant::Font) )
    {
        QSyntaxHighlighter::setFormat( start, count, format.value<QFont>() );
        return;
    }
}

void CustomSyntaxHighlighter::rehighlight()
{
    QSyntaxHighlighter::rehighlight();
}

int CustomSyntaxHighlighter::currentBlockState() const
{
    return QSyntaxHighlighter::currentBlockState();
}

void CustomSyntaxHighlighter::setCurrentBlockState(int blockState)
{
    if (blockState == currentBlockState())
    {
        return;
    }

    QSyntaxHighlighter::setCurrentBlockState(blockState);

    emit currentBlockStateChanged();
}


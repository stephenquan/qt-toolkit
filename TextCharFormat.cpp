#include "TextCharFormat.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

TextCharFormat::TextCharFormat(QObject* parent) :
    QObject(parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

TextCharFormat::TextCharFormat(const QColor& color, QObject* parent) :
    QObject(parent)
{
    setColor(color);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void TextCharFormat::setFont( const QFont& font )
{
    if ( font == QTextCharFormat::font() )
    {
        return;
    }

    QTextCharFormat::setFont(font);
    emit fontChanged();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QFont TextCharFormat::font() const
{
    return QTextCharFormat::font();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QColor TextCharFormat::color() const
{
    return QTextCharFormat::foreground().color();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void TextCharFormat::setColor( const QColor& color )
{
    if (TextCharFormat::color() == color)
    {
        return;
    }

    QTextCharFormat::setForeground( QBrush( color ) );
    emit colorChanged();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

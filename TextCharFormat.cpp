/*
 * COPYRIGHT 2019 ESRI
 *
 * TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
 * Unpublished material - all rights reserved under the
 * Copyright Laws of the United States and applicable international
 * laws, treaties, and conventions.
 *
 * For additional information, contact:
 * Environmental Systems Research Institute, Inc.
 * Attn: Contracts and Legal Services Department
 * 380 New York Street
 * Redlands, California, 92373
 * USA
 *
 * email: contracts@esri.com
 *
 */

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

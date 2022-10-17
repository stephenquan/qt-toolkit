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

#ifndef TextCharFormat_H
#define TextCharFormat_H

#include <QObject>
#include <QTextCharFormat>

//------------------------------------------------------------------------------

#define kTextCharFormatName                            "TextCharFormat"
#define kTextCharFormatVersionMajor                    kPluginVersionMajor
#define kTextCharFormatVersionMinor                    kPluginVersionMinor

//------------------------------------------------------------------------------

class TextCharFormat : public QObject, public QTextCharFormat
{
    Q_OBJECT

    Q_PROPERTY (QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY (QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    TextCharFormat(QObject* parent = nullptr);
    TextCharFormat(const QColor& color, QObject* parent = nullptr);

signals:
    void fontChanged();
    void colorChanged();

public:
    void setFont(const QFont& font);
    QFont font() const;

    QColor color() const;
    void setColor(const QColor& color);

};

//------------------------------------------------------------------------------

#endif

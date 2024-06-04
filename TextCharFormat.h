#ifndef TextCharFormat_H
#define TextCharFormat_H

#include <QObject>
#include <QTextCharFormat>

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

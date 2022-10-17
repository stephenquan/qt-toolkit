#include "SyntaxHighlighter.h"
#include <QQmlEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDebug>

/*
const QString SyntaxHighlighter::kLanguageNone = QStringLiteral("None");
const QString SyntaxHighlighter::kLanguageJavaScript = QStringLiteral("JavaScript");
const QString SyntaxHighlighter::kLanguageJSON = QStringLiteral("JSON");
const QString SyntaxHighlighter::kLanguageQML = QStringLiteral("QML");
const QString SyntaxHighlighter::kLanguageSQL = QStringLiteral("SQL");
const QString SyntaxHighlighter::kLanguageIni = QStringLiteral("ini");
const QString SyntaxHighlighter::kLanguagePython = QStringLiteral("Python");
const QString SyntaxHighlighter::kLanguageCpp = QStringLiteral("C++");
const QString SyntaxHighlighter::kLanguageShell = QStringLiteral("Shell");
const QString SyntaxHighlighter::kLanguageCustom = QStringLiteral("Custom");
*/

SyntaxHighlighter::SyntaxHighlighter( QObject* parent ) :
    QSyntaxHighlighter(parent),
    m_CaseSensitivity(Qt::CaseInsensitive),
    m_HashLineComments(false),
    m_SemiColonLineComments(false),
    m_DoubleSlashLineComments(false),
    m_DoubleDashLineComments(false),
    m_SlashStarBlockComments(false),
    m_SingleQuoteStrings(false),
    m_DoubleQuoteStrings(false),
    m_Numbers(false),
    m_Identifiers(false),
    m_CapitalTypes(false),
    m_Start(0),
    m_Pos(0),
    m_BlockState(BlockStateUnknown),
    m_CommentColor(Qt::darkGreen),
    m_StringColor(Qt::darkBlue),
    m_NumberColor(Qt::darkBlue),
    m_KeywordColor(Qt::darkCyan),
    m_IdentifierColor(Qt::darkRed),
    m_TypeColor(Qt::darkMagenta)
{
    setLanguageQML();
}

void SyntaxHighlighter::highlightBlock( const QString &text )
{
    m_Start = 0;
    m_Pos = 0;
    m_Text = text;
    m_BlockState = static_cast<BlockState>(QSyntaxHighlighter::previousBlockState());
    while (m_Pos < m_Text.length())
    {
        m_Ch = m_Text[m_Pos++];
        internalHighlightChar();
    }
    internalHighlightEOL();
    QSyntaxHighlighter::setCurrentBlockState(static_cast<int>(m_BlockState));

    //emit previousBlockStateChanged();
    //emit currentBlockStateChanged();
}

void SyntaxHighlighter::internalHighlightChar()
{
    switch (m_BlockState)
    {
    case BlockStateUnknown:
    case BlockStateNone:
        m_Start = m_Pos - 1;
        internalHighlightCharNone();
        break;

    case BlockStateSlash:
        internalHighlightCharSlash();
        break;

    case BlockStateDash:
        internalHighlightCharDash();
        break;

    case BlockStateSlashStarBlockComment:
        internalHighlightCharSlashStarBlockComment();
        break;

    case BlockStateSlashStarBlockCommentEnding:
        internalHighlightCharSlashStarBlockCommentEnding();
        break;

    case BlockStateSingleQuoteString:
        internalHighlightCharSingleQuoteString();
        break;

    case BlockStateDoubleQuoteString:
        internalHighlightCharDoubleQuoteString();
        break;

    case BlockStateNumber:
        internalHighlightCharNumber();
        break;

    case BlockStateIdentifierOrKeyword:
        internalHighlightCharIdentifierOrKeyword();
        break;

    default:
        break;
    }
}

void SyntaxHighlighter::internalHighlightCharNone()
{
    if (m_SingleQuoteStrings && m_Ch == '\'')
    {
        m_BlockState = BlockStateSingleQuoteString;
        return;
    }

    if (m_DoubleQuoteStrings && m_Ch == '"')
    {
        m_BlockState = BlockStateDoubleQuoteString;
        return;
    }

    if (m_Ch == '/')
    {
        m_BlockState = BlockStateSlash;
        return;
    }

    if (m_Ch == '-')
    {
        m_BlockState = BlockStateDash;
        return;
    }

    if (m_HashLineComments && m_Ch == '#')
    {
        m_BlockState = BlockStateHashLineComment;
        return;
    }

    if (m_SemiColonLineComments && m_Ch == ';')
    {
        m_BlockState = BlockStateSemiColonLineComment;
        return;
    }

    if (m_Numbers && m_Ch >= '0' && m_Ch <= '9')
    {
        m_BlockState = BlockStateNumber;
        return;
    }

    if (m_Ch.isLetter() || m_Ch == '_')
    {
        m_BlockState = BlockStateIdentifierOrKeyword;
        return;
    }
}

void SyntaxHighlighter::internalHighlightCharSlash()
{
    if (m_Ch == '/')
    {
        if (m_DoubleSlashLineComments)
        {
            m_BlockState = BlockStateDoubleSlashLineComment;
            return;
        }

        m_BlockState = BlockStateSlash;
        m_Start = m_Pos - 1;
        return;
    }

    if (m_SlashStarBlockComments && m_Ch == '*')
    {
        m_BlockState = BlockStateSlashStarBlockComment;
        return;
    }

    m_Pos--;
    m_BlockState = BlockStateNone;
}

void SyntaxHighlighter::internalHighlightCharDash()
{
    if (m_Ch == '-')
    {
        if (m_DoubleDashLineComments)
        {
            m_BlockState = BlockStateDoubleDashLineComment;
            return;
        }

        m_BlockState = BlockStateSlash;
        m_Start = m_Pos - 1;
        return;
    }

    m_Pos--;
    m_BlockState = BlockStateNone;
}

void SyntaxHighlighter::internalHighlightCharSlashStarBlockComment()
{
    if (m_Ch == '*')
    {
        m_BlockState = BlockStateSlashStarBlockCommentEnding;
        return;
    }
}

void SyntaxHighlighter::internalHighlightCharSlashStarBlockCommentEnding()
{
    if (m_Ch == '*')
    {
        return;
    }

    if (m_Ch == '/')
    {
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_CommentColor);
        m_Pos--;
        m_BlockState = BlockStateNone;
        return;
    }

    m_BlockState = BlockStateSlashStarBlockComment;
}

void SyntaxHighlighter::internalHighlightCharSingleQuoteString()
{
    if (m_Ch == '\'')
    {
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_StringColor);
        m_BlockState = BlockStateNone;
        return;
    }
}

void SyntaxHighlighter::internalHighlightCharDoubleQuoteString()
{
    if (m_Ch == '"')
    {
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_StringColor);
        m_BlockState = BlockStateNone;
        return;
    }
}

void SyntaxHighlighter::internalHighlightCharNumber()
{
    if ((m_Ch >= '0' && m_Ch <= '9')
            || m_Ch == 'e' || m_Ch == 'E'
            || m_Ch == 'f' || m_Ch == 'F'
            || m_Ch == 'g' || m_Ch == 'G'
            || m_Ch == '-' || m_Ch == '+'
            || m_Ch == '.')
    {
        return;
    }

    m_Pos--;
    foundNumber();
}

void SyntaxHighlighter::internalHighlightCharIdentifierOrKeyword()
{
    if (m_Ch.isLetterOrNumber() || m_Ch == '_')
    {
        return;
    }

    m_Pos--;
    foundIdentifierOrKeyword();
}

QColor SyntaxHighlighter::identifierOrKeywordFormat(const QString& identifierOrKeyword) const
{
    foreach (QString keyword, m_KeywordList)
    {
        if (identifierOrKeyword.compare(keyword, m_CaseSensitivity) == 0)
        {
            return m_KeywordColor;
        }
    }

    if (m_CapitalTypes && identifierOrKeyword.length() > 0 && identifierOrKeyword[0].isUpper())
    {
        return m_TypeColor;
    }

    if (m_Identifiers)
    {
        return m_IdentifierColor;
    }

    return QColor();
}

void SyntaxHighlighter::internalHighlightEOL()
{
    switch (m_BlockState)
    {

    case BlockStateSingleQuoteString:
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_StringColor);
        return;

    case BlockStateDoubleQuoteString:
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_StringColor);
        return;

    case BlockStateSlash:
        m_BlockState = BlockStateNone;
        return;

    case BlockStateSlashStarBlockComment:
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_CommentColor);
        return;

    case BlockStateSlashStarBlockCommentEnding:
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_CommentColor);
        m_BlockState = BlockStateSlashStarBlockComment;
        return;

    case BlockStateHashLineComment:
    case BlockStateSemiColonLineComment:
    case BlockStateDoubleSlashLineComment:
    case BlockStateDoubleDashLineComment:
        QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_CommentColor);
        m_BlockState = BlockStateNone;
        return;

    case BlockStateNumber:
        foundNumber();
        return;

    case BlockStateIdentifierOrKeyword:
        foundIdentifierOrKeyword();
        return;

    default:
        break;
    }
}

QVariant SyntaxHighlighter::textDocument() const
{
    return m_TextDocument;
}

void SyntaxHighlighter::setTextDocument( const QVariant& textDocument )
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

/*
void SyntaxHighlighter::setFormat( int start, int count, const QVariant& format )
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
*/

void SyntaxHighlighter::rehighlight()
{
    QSyntaxHighlighter::rehighlight();
}

void SyntaxHighlighter::foundIdentifierOrKeyword()
{
    QString identifierOrKeyword = m_Text.mid(m_Start, m_Pos - m_Start);
    QColor color = identifierOrKeywordFormat(identifierOrKeyword);
    if (!color.isValid())
    {
        m_BlockState = BlockStateNone;
        return;
    }
    QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, color);
    m_BlockState = BlockStateNone;
}

void SyntaxHighlighter::foundNumber()
{
    QSyntaxHighlighter::setFormat(m_Start, m_Pos - m_Start, m_NumberColor);
    m_BlockState = BlockStateNone;
}

void SyntaxHighlighter::setLanguage(SyntaxHighlighter::Language language)
{
    // setLanguageNone();
    setLanguageQML();
    rehighlight();
}

void SyntaxHighlighter::setLanguageNone()
{
    setKeywords("");
    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(false);
    setSingleQuoteStrings(false);
    setDoubleQuoteStrings(false);
    setNumbers(false);
    setIdentifiers(false);
    setCapitalTypes(false);
}

/*
void SyntaxHighlighter::setLanguageJavaScript()
{
    setKeywords(
        "break case catch class const continue debugger default delete do else export "
        "extends finally for function if import in instanceof new return super switch "
        "this throw try typeof var void while with yield "
        "enum "
        "implements interface let package private protected public static yield "
        "await async "
        "abstract boolean byte char double final float goto int long native short "
        "synchronized throws transient volatile "
        "null true false "
        );

    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(true);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(true);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(false);
}
*/

/*
void SyntaxHighlighter::setLanguageJSON()
{
    setKeywords("");

    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(false);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(false);
}
*/

void SyntaxHighlighter::setLanguageQML()
{
    setKeywords(
        "break case catch class const continue debugger default delete do else export "
        "extends finally for function if import in instanceof new return super switch "
        "this throw try typeof var void while with yield "
        "enum "
        "implements interface let package private protected public static yield "
        "await async "
        "abstract boolean byte char double final float goto int long native short "
        "synchronized throws transient volatile "
        "null true false "
        );

    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(true);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(true);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(true);
}

/*
void SyntaxHighlighter::setLanguageSQL()
{
    setKeywords(
        "abort action add after all alter always analyze and as asc attach "
        "autoincrement before begin between by cascade case cast check collate "
        "column commit conflict constraint create cross current current_date "
        "current_time current_timestamp database default deferrable deferred "
        "delete desc detach distinct do drop each else end escape except exclude "
        "exclusive exists explain fail filter first following for foreign from "
        "full generated glob group groups having if ignore immediate in index "
        "indexed initially inner insert instead intersect into is isnull join "
        "key last left like limit match natural no not nothing notnull null nulls "
        "of offset on or order others outer over partition plan pragma preceding "
        "primary query raise range recursive references regexp reindex release "
        "rename replace restrict right rollback row rows savepoint select set "
        "table temp temporary then ties to transaction trigger unbounded union "
        "unique update using vacuum values view virtual when where window with without "
        );

    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(true);
    setSlashStarBlockComments(true);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(false);
}
*/

/*
void SyntaxHighlighter::setLanguageIni()
{
    setKeywords("");

    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(true);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(false);
    setSingleQuoteStrings(false);
    setDoubleQuoteStrings(false);
    setNumbers(true);
    setIdentifiers(false);
    setCapitalTypes(false);
}
*/

/*
void SyntaxHighlighter::setLanguagePython()
{
    setKeywords(
        "False await else import pass None break except in raise"
        "True class finally is return "
        "and continue for lambda try as def from nonlocal while "
        "assert del global not with "
        "async elif if or yield "
        );

    setCaseSensitivity(Qt::CaseSensitive);
    setHashLineComments(true);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(false);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(false);
}
*/

/*
void SyntaxHighlighter::setLanguageCpp()
{
    setKeywords(
        "alignas alignof and and_eq asm atomic_cancel atomic_commit atomic_noexcept "
        "auto bitand bitor bool break case catch char char8_t char16_t char32_t "
        "class compl concept const consteval constexpr constinit const_cast continue "
        "co_await co_return co_yield decltype default delete do double dynamic_cast "
        "else enum explicit export extern false float for friend goto if inline "
        "int long mutable namespace new noexcept not not_eq nullptr operator or "
        "or_eq private protected public reflexpr register reinterpret_cast requires "
        "return short signed sizeof static static_assert static_cast struct switch "
        "synchronized template this thread_local throw true try typedef typeid typename "
        "union unsigned using virtual void volatile wchar_t while xor xor_eq "
        );

    setCaseSensitivity(Qt::CaseSensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(true);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(true);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(false);
}
*/

/*
void SyntaxHighlighter::setLanguageShell()
{
    setKeywords(
        "case do done elif else esac fi for function "
        "if in select then time until while "
        );

    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(true);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(false);
    setSingleQuoteStrings(true);
    setDoubleQuoteStrings(true);
    setNumbers(true);
    setIdentifiers(true);
    setCapitalTypes(false);
}
*/

/*
void SyntaxHighlighter::setLanguageCustom()
{
    setKeywords("");
    setCaseSensitivity(Qt::CaseInsensitive);
    setHashLineComments(false);
    setSemiColonLineComments(false);
    setDoubleSlashLineComments(false);
    setDoubleDashLineComments(false);
    setSlashStarBlockComments(false);
    setSingleQuoteStrings(false);
    setDoubleQuoteStrings(false);
    setNumbers(false);
    setIdentifiers(false);
    setCapitalTypes(false);
}
*/

void SyntaxHighlighter::setKeywords(const QString& keywords)
{
    if (m_Keywords == keywords)
    {
        return;
    }

    m_Keywords = keywords;
    m_KeywordList = m_Keywords.split(" ");
}

void SyntaxHighlighter::setCurrentBlockState(int blockState)
{
    if (blockState == currentBlockState())
    {
        return;
    }

    QSyntaxHighlighter::setCurrentBlockState(blockState);

    //emit currentBlockStateChanged();
}

/*
void SyntaxHighlighter::setLanguageReply(QNetworkReply* reply)
{
    if (m_LanguageReply == reply)
    {
        return;
    }

    if (m_LanguageReply)
    {
        disconnect(m_LanguageReply, &QNetworkReply::finished, this, &SyntaxHighlighter::onFinished);
        m_LanguageReply->deleteLater();
        m_LanguageReply = nullptr;
    }

    m_LanguageReply = reply;

    if (!m_LanguageReply)
    {
        return;
    }

    connect(m_LanguageReply, &QNetworkReply::finished, this, &SyntaxHighlighter::onFinished);
}
*/

/*
void SyntaxHighlighter::onFinished()
{
    if (!m_LanguageReply)
    {
        return;
    }

    QByteArray response = m_LanguageReply->readAll();

    setLanguageReply(nullptr);

    if (response.isEmpty())
    {
        qDebug() << "Unexpected: No Language Data";
        return;
    }

    setLanguage(response);
}
*/

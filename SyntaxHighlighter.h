#ifndef SyntaxHighlighter_H
#define SyntaxHighlighter_H

#include <QObject>
#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QQuickTextDocument>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QColor>
#include "TextCharFormat.h"

#define kSyntaxHighlighterName                            "SyntaxHighlighter"
#define kSyntaxHighlighterVersionMajor                    kPluginVersionMajor
#define kSyntaxHighlighterVersionMinor                    kPluginVersionMinor

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    //Q_PROPERTY(int previousBlockState READ previousBlockState NOTIFY previousBlockStateChanged)
    //Q_PROPERTY(int currentBlockState READ currentBlockState WRITE setCurrentBlockState NOTIFY currentBlockStateChanged)
    Q_PROPERTY(QVariant textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(SyntaxHighlighter::Language language READ language WRITE setLanguage NOTIFY languageChanged)

public:
    enum BlockState
    {
        BlockStateUnknown = -1,
        BlockStateNone,
        BlockStateIdentifierOrKeyword,
        BlockStateNumber,
        BlockStateSlash,
        BlockStateDash,
        BlockStateHashLineComment,
        BlockStateSemiColonLineComment,
        BlockStateDoubleSlashLineComment,
        BlockStateDoubleDashLineComment,
        BlockStateSlashStarBlockComment,
        BlockStateSlashStarBlockCommentEnding,
        BlockStateSingleQuoteString,
        BlockStateSingleQuoteStringEscape,
        BlockStateDoubleQuoteString,
        BlockStateDoubleQuoteStringEscape,
        BlockStateBackTick
    };

    enum Language
    {
        LanguageNone,
        LanguageQML,
        LanguageCustom = -1
    };

    Q_ENUMS(BlockState Language)

public:
    SyntaxHighlighter(QObject* parent = nullptr);

    //Q_INVOKABLE void setFormat(int start, int count, const QVariant& format);
    Q_INVOKABLE void rehighlight();

signals:
    void textDocumentChanged();
    void languageChanged();
    //void previousBlockStateChanged();
    //void currentBlockStateChanged();

    //void highlightBlockText(const QString& text);

private slots:
    //void onFinished();

protected:
    QVariant m_TextDocument;
    SyntaxHighlighter::Language m_Language;
    QString m_Keywords;
    QStringList m_KeywordList;
    Qt::CaseSensitivity m_CaseSensitivity;
    bool m_HashLineComments;
    bool m_SemiColonLineComments;
    bool m_DoubleSlashLineComments;
    bool m_DoubleDashLineComments;
    bool m_SlashStarBlockComments;
    bool m_SingleQuoteStrings;
    bool m_DoubleQuoteStrings;
    bool m_Numbers;
    bool m_Identifiers;
    bool m_CapitalTypes;
    QColor m_CommentColor;
    QColor m_StringColor;
    QColor m_NumberColor;
    QColor m_KeywordColor;
    QColor m_IdentifierColor;
    QColor m_TypeColor;

    // Languages
    //static const QString kLanguageNone;
    //static const QString kLanguageJavaScript;
    //static const QString kLanguageJSON;
    //static const QString kLanguageQML;
    //static const QString kLanguageSQL;
    //static const QString kLanguageIni;
    //static const QString kLanguagePython;
    //static const QString kLanguageCpp;
    //static const QString kLanguageShell;
    //static const QString kLanguageCustom;

    // Internal
    QString m_Text;
    int m_Start;
    int m_Pos;
    QChar m_Ch;
    BlockState m_BlockState;

    void setCurrentBlockState(int blockState);

    QVariant textDocument() const;
    void setTextDocument(const QVariant& textDocument);

    SyntaxHighlighter::Language language() const { return m_Language; }
    void setLanguage(SyntaxHighlighter::Language language);

    void setKeywords(const QString& keywords);
    void setCaseSensitivity(Qt::CaseSensitivity caseSensitivity) { m_CaseSensitivity = caseSensitivity; }
    void setHashLineComments(bool hashLineComments) { m_HashLineComments = hashLineComments; }
    void setSemiColonLineComments(bool semiColonLineComments) { m_SemiColonLineComments = semiColonLineComments; }
    void setDoubleSlashLineComments(bool doubleSlashLineComments) { m_DoubleSlashLineComments = doubleSlashLineComments; }
    void setDoubleDashLineComments(bool doubleDashLineComments) { m_DoubleDashLineComments = doubleDashLineComments; }
    void setSlashStarBlockComments(bool slashStarBlockComments) { m_SlashStarBlockComments = slashStarBlockComments; }
    void setSingleQuoteStrings(bool singleQuoteStrings) { m_SingleQuoteStrings = singleQuoteStrings; }
    void setDoubleQuoteStrings(bool doubleQuoteStrings) { m_DoubleQuoteStrings = doubleQuoteStrings; }
    void setNumbers(bool numbers) { m_Numbers = numbers; }
    void setIdentifiers(bool identifiers) { m_Identifiers = identifiers; }
    void setCapitalTypes(bool capitalTypes) { m_CapitalTypes = capitalTypes; }

    virtual void highlightBlock(const QString &text);

protected:
    void setLanguageNone();
    //void setLanguageJavaScript();
    //void setLanguageJSON();
    void setLanguageQML();
    //void setLanguageSQL();
    //void setLanguageIni();
    //void setLanguagePython();
    //void setLanguageCpp();
    //void setLanguageShell();
    //void setLanguageCustom();

    void internalHighlightChar();
    void internalHighlightCharNone();
    void internalHighlightCharSlash();
    void internalHighlightCharSlashStarBlockComment();
    void internalHighlightCharSlashStarBlockCommentEnding();
    void internalHighlightCharDash();
    void internalHighlightCharSingleQuoteString();
    void internalHighlightCharDoubleQuoteString();
    void internalHighlightCharNumber();
    void internalHighlightCharIdentifierOrKeyword();
    void internalHighlightCharBackTick();
    void internalHighlightEOL();
    void foundIdentifierOrKeyword();
    void foundNumber();

    QColor identifierOrKeywordFormat(const QString& identifierOrKeyword) const;

};

#endif

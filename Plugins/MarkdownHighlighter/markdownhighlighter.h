#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class MarkdownHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    MarkdownHighlighter(QTextDocument *parent = 0);
    void highlightBlock(const QString &text);
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> HighlightingRules;

    QTextCharFormat headingFormat;
    QTextCharFormat boldFormat;
    QTextCharFormat italicFormat;
    QTextCharFormat strikethroughFormat;
    QTextCharFormat imageFormat;
    QTextCharFormat linkFormat;
    QTextCharFormat autolinkFormat;
    QTextCharFormat quoteFormat;
    QTextCharFormat codeFormat;
    QTextCharFormat inlineCodeFormat;
    QTextCharFormat orderedListFormat;
signals:

public slots:

};

#endif // MARKDOWNHIGHLIGHTER_H

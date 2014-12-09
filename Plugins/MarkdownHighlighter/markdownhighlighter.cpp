#include "markdownhighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    headingFormat.setFontPointSize(25);
    headingFormat.setForeground(Qt::darkBlue);
    headingFormat.setFontWeight(QFont::Bold);
    rule.format = headingFormat;
    rule.pattern = QRegExp(".+\n={1,6}");
    HighlightingRules.append(rule);

    boldFormat.setFontWeight(QFont::Bold);
    boldFormat.setForeground(Qt::red);
    rule.format = boldFormat;
    rule.pattern = QRegExp("*.+*");
    HighlightingRules.append(rule);

    italicFormat.setFontWeight(QFont::Bold);
    italicFormat.setForeground(Qt::red);
    rule.format = boldFormat;
    rule.pattern = QRegExp("_.+_");
    HighlightingRules.append(rule);

    strikethroughFormat.setFontWeight(QFont::Bold);
    strikethroughFormat.setForeground(Qt::red);
    rule.format = strikethroughFormat;
    rule.pattern = QRegExp("~~.+~~");
    HighlightingRules.append(rule);

    codeFormat.setFontWeight(QFont::StyleItalic);
    codeFormat.setForeground(Qt::darkGray);
    rule.format = codeFormat;
    rule.pattern = QRegExp("\t.+");
    HighlightingRules.append(rule);

    inlineCodeFormat.setFontWeight(QFont::StyleItalic);
    inlineCodeFormat.setForeground(Qt::darkGreen);
    rule.format = inlineCodeFormat;
    rule.pattern = QRegExp("`.+`");
    HighlightingRules.append(rule);

    quoteFormat.setFontWeight(QFont::StyleItalic);
    quoteFormat.setForeground(Qt::darkGray);
    rule.format = quoteFormat;
    rule.pattern = QRegExp(">.+");
    HighlightingRules.append(rule);

    orderedListFormat.setFontWeight(QFont::StyleItalic);
    orderedListFormat.setForeground(Qt::darkBlue);
    rule.format = orderedListFormat;
    rule.pattern = QRegExp("[1-9]. .+");
    HighlightingRules.append(rule);

    autolinkFormat.setFontWeight(QFont::StyleItalic);
    autolinkFormat.setForeground(Qt::darkBlue);
    rule.format = autolinkFormat;
    rule.pattern = QRegExp("<http://.+>");
    HighlightingRules.append(rule);

}

void MarkdownHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, HighlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}

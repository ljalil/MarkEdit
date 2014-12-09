#include "markdownconverter.h"

MarkdownConverter::MarkdownConverter(QObject *parent) :
    QObject(parent)
{
}

QString MarkdownConverter::convertMarkdown(QString html)
{
    MMIOT* document = 0;
    char* result = 0;
    QByteArray data = html.toUtf8();
    document = mkd_string(data.data(),data.length(),0);
    mkd_compile(document,0);
    mkd_document(document,&result);
    QString renderedHtml = QString::fromUtf8(result);
    return renderedHtml;
}

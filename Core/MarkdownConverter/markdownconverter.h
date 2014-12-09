#ifndef MARKDOWNCONVERTER_H
#define MARKDOWNCONVERTER_H

#include <QObject>
extern "C" {
#include <mkdio.h>
}
class MarkdownConverter : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConverter(QObject *parent = 0);
    QString convertMarkdown(QString html);

signals:
    void htmlReady(QString);

};

#endif // MARKDOWNCONVERTER_H

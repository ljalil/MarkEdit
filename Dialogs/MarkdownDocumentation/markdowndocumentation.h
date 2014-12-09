#ifndef MARKDOWNDOCUMENTATION_H
#define MARKDOWNDOCUMENTATION_H

#include <QDialog>
#include <QFile>
#include "../../Core/MarkdownConverter/markdownconverter.h"

namespace Ui {
class MarkdownDocumentation;
}

class MarkdownDocumentation : public QDialog
{
    Q_OBJECT

public:
    explicit MarkdownDocumentation(QWidget *parent = 0);
    ~MarkdownDocumentation();

private:
    Ui::MarkdownDocumentation *ui;
    QFile *documentationLoader;
    MarkdownConverter *converter;

};

#endif // MARKDOWNDOCUMENTATION_H

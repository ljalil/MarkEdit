#include "markdowndocumentation.h"
#include "ui_markdowndocumentation.h"

MarkdownDocumentation::MarkdownDocumentation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkdownDocumentation)
{
    ui->setupUi(this);
    documentationLoader = new QFile("://Documents/MarkdownDocumentation.md");
    converter = new MarkdownConverter;
    QObject::connect(ui->CloseButton,SIGNAL(clicked()),this,SLOT(accept()));
    documentationLoader->open(QIODevice::ReadOnly | QIODevice::Text);
    ui->DocumentationViewer->setHtml(converter->convertMarkdown(documentationLoader->readAll()));
    documentationLoader->close();
}

MarkdownDocumentation::~MarkdownDocumentation()
{
    delete documentationLoader;
    delete converter;
    delete ui;
}

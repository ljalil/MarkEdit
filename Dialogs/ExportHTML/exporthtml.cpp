#include "exporthtml.h"
#include "ui_exporthtml.h"

ExportHTML::ExportHTML(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportHTML)
{
    ui->setupUi(this);
    outputFile = new QFile();
    QObject::connect(ui->chooseFile_ToolButton,SIGNAL(clicked()),this,SLOT(chooseFileDialog()));
}

ExportHTML::~ExportHTML()
{
    delete outputFile;
    delete ui;
}

void ExportHTML::setHtml(const QString &html)
{
    this->htmlSource = html;
}

void ExportHTML::chooseFileDialog()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "Choose output file",
                                                QDir::homePath(),
                                                "HTML file (*.htm *.html)"
                                                );
    ui->OutputFile_LineEdit->setText(path);
}

void ExportHTML::exportHTML()
{
    this->outputPath = ui->OutputFile_LineEdit->text();
    if (!this->outputPath.isEmpty()) {
        this->outputFile->setFileName(this->outputPath);
        this->outputFile->open(QIODevice::WriteOnly | QIODevice::Text);
        if( this->outputFile->isWritable() )
            this->outputFile->write(this->htmlSource.toUtf8());
        else
            QMessageBox::information(this,"File device writing error","Cannot write to output file, do you have write permission to this file?");
    } else {
        QMessageBox::information(this,"Output target error","You didn't choose any output file, please choose one before exporting.");
        return;
    }
    this->outputFile->close();
}

#include "exportpdf.h"
#include "ui_exportpdf.h"

ExportPDF::ExportPDF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportPDF)
{
    ui->setupUi(this);
}

ExportPDF::~ExportPDF()
{
    delete ui;
}

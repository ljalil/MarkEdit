#ifndef EXPORTPDF_H
#define EXPORTPDF_H

#include <QDialog>

namespace Ui {
class ExportPDF;
}

class ExportPDF : public QDialog
{
    Q_OBJECT

public:
    explicit ExportPDF(QWidget *parent = 0);
    ~ExportPDF();

private:
    Ui::ExportPDF *ui;
};

#endif // EXPORTPDF_H

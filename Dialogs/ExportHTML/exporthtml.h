#ifndef EXPORTHTML_H
#define EXPORTHTML_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class ExportHTML;
}

class ExportHTML : public QDialog
{
    Q_OBJECT

public:
    explicit ExportHTML(QWidget *parent = 0);
    ~ExportHTML();
    void setHtml(const QString &html);

private:
    Ui::ExportHTML *ui;
    QFile *outputFile;
    QString outputPath;
    QString htmlSource;

public slots:
    void chooseFileDialog();
    void exportHTML();
};

#endif // EXPORTHTML_H

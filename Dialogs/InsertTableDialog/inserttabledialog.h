#ifndef INSERTTABLEDIALOG_H
#define INSERTTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class InsertTableDialog;
}

class InsertTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertTableDialog(QWidget *parent = 0);
    ~InsertTableDialog();
    QString table() const;
    QString generateTable();
private slots:
    void on_autoPreview_CheckBox_clicked();
    void on_preview_Button_clicked();
    void on_rowsNumber_SpinBox_valueChanged(int arg1);
    void on_columnsNumber_SpinBox_valueChanged(int arg1);

private:
    Ui::InsertTableDialog *ui;
    QString tbl;

};

#endif // INSERTTABLEDIALOG_H

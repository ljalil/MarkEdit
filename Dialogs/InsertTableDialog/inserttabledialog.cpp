#include "inserttabledialog.h"
#include "ui_inserttabledialog.h"
#include <QDebug>
InsertTableDialog::InsertTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertTableDialog)
{
    ui->setupUi(this);
}

InsertTableDialog::~InsertTableDialog()
{
    delete ui;
}

void InsertTableDialog::on_autoPreview_CheckBox_clicked()
{
    if (ui->autoPreview_CheckBox->isChecked()) {
        ui->preview_Button->setDisabled(true);
        ui->tablePreview_TextEdit->setText(generateTable());
    } else if (!ui->autoPreview_CheckBox->isChecked())
        ui->preview_Button->setEnabled(true);
}

QString InsertTableDialog::generateTable()
{
    int columns = ui->columnsNumber_SpinBox->value();
    int rows = ui->rowsNumber_SpinBox->value();
    QString table;
    for (int columnIndex = 0; columnIndex <= columns; columnIndex++) {
        table.append("|    ");
    }
    table.append('\n');
    for (int columnIndex = 0; columnIndex < columns; columnIndex++) {
        table.append("|----");
    }
    table.append("|");
    table.append('\n');

    for (int rowIndex = 0; rowIndex < rows-1; rowIndex++) {
        for (int columnIndex = 0; columnIndex <= columns; columnIndex++) {
            table.append("|    ");
        }
        table.append('\n');
    }
    this->tbl = table;
    return table;
}

void InsertTableDialog::on_preview_Button_clicked()
{
    ui->tablePreview_TextEdit->setText(generateTable());
}

void InsertTableDialog::on_rowsNumber_SpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    if (ui->autoPreview_CheckBox->isChecked())
        ui->tablePreview_TextEdit->setText(generateTable());
}

void InsertTableDialog::on_columnsNumber_SpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    if (ui->autoPreview_CheckBox->isChecked())
        ui->tablePreview_TextEdit->setText(generateTable());
}

QString InsertTableDialog::table() const
{
    return this->tbl;
}

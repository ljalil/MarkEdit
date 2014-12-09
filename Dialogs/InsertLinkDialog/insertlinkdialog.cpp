#include "insertlinkdialog.h"
#include "ui_insertlinkdialog.h"

InsertLinkDialog::InsertLinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertLinkDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->ReferenceStyle_CheckBox,SIGNAL(toggled(bool)),this,SLOT(activateReferenceWidgets(bool)));
}

InsertLinkDialog::~InsertLinkDialog()
{
    delete ui;
}

QString InsertLinkDialog::getLinkURL() const
{
    return this->linkURL;
}

QString InsertLinkDialog::getLinkLabel() const
{
    return this->linkLabel;
}

QString InsertLinkDialog::getReferenceName() const
{
    return this->referenceName;
}

bool InsertLinkDialog::getReferenceType() const
{
    return this->referenceType;
}

void InsertLinkDialog::on_InsertLinkDialog_accepted()
{
    this->linkLabel = ui->linkLabelLineEdit->text();
    this->linkURL = ui->linkUrlLineEdit->text();
    if( ui->ReferenceStyle_CheckBox->isChecked() ) {
        this->referenceType = true;
        this->referenceName = ui->linkReferenceName_LineEdit->text();
    } else {
        this->referenceType = false;
    }
}

void InsertLinkDialog::activateReferenceWidgets(bool active)
{
    if (active) {
        ui->linkReferenceName->setEnabled(true);
        ui->linkReferenceName_LineEdit->setEnabled(true);
    } else {
        ui->linkReferenceName->setEnabled(false);
        ui->linkReferenceName_LineEdit->setEnabled(false);
    }
}

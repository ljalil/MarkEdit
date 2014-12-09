#include "insertimagedialog.h"
#include "ui_insertimagedialog.h"

InsertImageDialog::InsertImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertImageDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->ReferenceStyleRadioButton,SIGNAL(toggled(bool)),this,SLOT(activateReferenceWidgets(bool)));
}

InsertImageDialog::~InsertImageDialog()
{
    delete ui;
}

QString InsertImageDialog::getImageURL() const
{
    return this->imageURL;
}

QString InsertImageDialog::getImageAlt() const
{
    return this->imageAlt;
}

QString InsertImageDialog::getImageTooltip() const
{
    return this->imageTooltip;
}

QString InsertImageDialog::getImageReferenceName() const
{
    return this->imageReferenceName;
}

bool InsertImageDialog::getReferenceType() const
{
    return this->referenceType;
}

void InsertImageDialog::activateReferenceWidgets(bool active)
{
    if (active) {
        ui->ReferenceNameLineEdit->setEnabled(true);
        ui->ReferenceNameLabel->setEnabled(true);
    } else {
        ui->ReferenceNameLineEdit->setEnabled(false);
        ui->ReferenceNameLabel->setEnabled(false);
    }

}

void InsertImageDialog::on_buttonBox_accepted()
{
    this->imageURL = ui->ImageURLLineEdit->text();
    this->imageTooltip = ui->TooltipLineEdit->text();
    this->imageAlt = ui->AlternativeLineEdit->text();
    this->imageReferenceName = ui->ReferenceNameLineEdit->text();
    if(ui->InlineStyleRadioButton->isChecked())
        this->referenceType = false;
    else if(ui->ReferenceStyleRadioButton->isChecked())
        this->referenceType = true;
}

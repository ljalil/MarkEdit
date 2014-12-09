#ifndef INSERTLINKDIALOG_H
#define INSERTLINKDIALOG_H

#include <QDialog>

namespace Ui {
class InsertLinkDialog;
}

class InsertLinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertLinkDialog(QWidget *parent = 0);
    ~InsertLinkDialog();
    QString getLinkURL() const;
    QString getLinkLabel() const;
    QString getReferenceName() const;
    bool getReferenceType() const;
private slots:
    void on_InsertLinkDialog_accepted();
    void activateReferenceWidgets(bool active);
private:
    Ui::InsertLinkDialog *ui;
    QString linkURL;
    QString linkLabel;
    QString referenceName;
    bool referenceType;
};

#endif // INSERTLINKDIALOG_H

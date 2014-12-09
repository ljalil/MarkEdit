#ifndef INSERTIMAGEDIALOG_H
#define INSERTIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class InsertImageDialog;
}

class InsertImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertImageDialog(QWidget *parent = 0);
    ~InsertImageDialog();
    QString getImageURL() const;
    QString getImageAlt() const;
    QString getImageTooltip() const;
    QString getImageReferenceName() const;
    bool getReferenceType() const;
private slots:
    void activateReferenceWidgets(bool active);

    void on_buttonBox_accepted();

private:
    Ui::InsertImageDialog *ui;
    QString imageURL;
    QString imageAlt;
    QString imageTooltip;
    QString imageReferenceName;
    bool referenceType;
};

#endif // INSERTIMAGEDIALOG_H

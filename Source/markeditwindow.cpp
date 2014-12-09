#include "markeditwindow.h"
#include "ui_markeditwindow.h"
#include "Dialogs/InsertImageDialog/insertimagedialog.h"
#include "Dialogs/InsertLinkDialog/insertlinkdialog.h"
#include "Dialogs/InsertTableDialog/inserttabledialog.h"
#include "Dialogs/MarkdownDocumentation/markdowndocumentation.h"
#include "Dialogs/AboutDialog/aboutdialog.h"
#include "Dialogs/ExportHTML/exporthtml.h"
#include "Dialogs/ExportPDF/exportpdf.h"

MarkEditWindow::MarkEditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MarkEditWindow)
{
    ui->setupUi(this);
    initFileSystemModel();
    initDocumentsListModel();
    ui->MarkdownEditor->setFont(QFont("SourceCodePro"));
    autoPreview = true;
    this->converter = new MarkdownConverter(this);
    this->Handler = new DocumentsHandler(this);
    Highlighter = new MarkdownHighlighter(ui->MarkdownEditor->document());
    MarkEditSettings = new QSettings("abdeljalil","MarkEdit");
    ui->MarkdownPreview->settings()->setUserStyleSheetUrl(QUrl("qrc:/Stylesheet/default.css"));

    //to join Horizontal Vertical actions on one execlusive group.
    orientationGroup = new QActionGroup(this);
    this->orientationGroup->addAction(ui->actionVertical);
    this->orientationGroup->addAction(ui->actionHorizontal);

    QObject::connect(ui->actionOpen,               SIGNAL(triggered()),this,               SLOT(openNewFile()));
    QObject::connect(ui->actionSaveAs,             SIGNAL(triggered()),this,               SLOT(saveCurrentFileAs()));
    QObject::connect(ui->actionSave,               SIGNAL(triggered()),this,               SLOT(saveCurrentFile()));
    QObject::connect(this,                         SIGNAL(sourceChanged(QString)),this,    SLOT(setOutput(QString)));
    QObject::connect(ui->actionClose,              SIGNAL(triggered()),this,               SLOT(closeCurrentFile()));
    QObject::connect(ui->actionFileExplorer,       SIGNAL(toggled(bool)),this,             SLOT(fileSystemVisibility(bool)));
    QObject::connect(ui->actionDocumentsList,      SIGNAL(triggered(bool)),this,           SLOT(documentListVisibility(bool)));
    QObject::connect(ui->actionMarkdownEditor,     SIGNAL(toggled(bool)),this,             SLOT(markdownEditorVisibility(bool)));
    QObject::connect(ui->actionHTMLPreview,        SIGNAL(triggered(bool)),this,           SLOT(HTMLPreviewVisibility(bool)));

    QObject::connect(ui->actionFormatBold,         SIGNAL(triggered()),this,               SLOT(insertFormatBold()));
    QObject::connect(ui->actionFormatItalic,       SIGNAL(triggered()),this,               SLOT(insertFormatItalic()));
    QObject::connect(ui->actionFormatStrikethrough,SIGNAL(triggered()),this,               SLOT(insertFormatStrikethrough()));

    QObject::connect(ui->actionBlockQuote,         SIGNAL(triggered()),this,               SLOT(insertBlockquote()));
    QObject::connect(ui->actionCode,               SIGNAL(triggered()),this,               SLOT(insertCode()));

    QObject::connect(ui->actionInsertHeadingOne,   SIGNAL(triggered()),this,               SLOT(insertHeadingOne()));
    QObject::connect(ui->actionInsertHeadingTwo,   SIGNAL(triggered()),this,               SLOT(insertHeadingTwo()));
    QObject::connect(ui->actionInsertHeadingThree, SIGNAL(triggered()),this,               SLOT(insertHeadingThree()));
    QObject::connect(ui->actionInsertHeadingFour,  SIGNAL(triggered()),this,               SLOT(insertHeadingFour()));
    QObject::connect(ui->actionInsertHeadingFive,  SIGNAL(triggered()),this,               SLOT(insertHeadingFive()));
    QObject::connect(ui->actionInsertHeadingSix,   SIGNAL(triggered()),this,               SLOT(insertHeadingSix()));

    QObject::connect(ui->actionCopyAsHTML,SIGNAL(triggered()),this,SLOT(copyAsHTML()));
    QObject::connect(ui->actionCopy,               SIGNAL(triggered()),ui->MarkdownEditor, SLOT(copy()));
    QObject::connect(ui->actionCut,                SIGNAL(triggered()),ui->MarkdownEditor, SLOT(cut()));
    QObject::connect(ui->actionPaste,              SIGNAL(triggered()),ui->MarkdownEditor, SLOT(paste()));

    QObject::connect(ui->actionUndo,               SIGNAL(triggered()),ui->MarkdownEditor, SLOT(undo()));
    QObject::connect(ui->actionRedo,               SIGNAL(triggered()),ui->MarkdownEditor, SLOT(redo()));

    QObject::connect(ui->actionSelectAll,          SIGNAL(triggered()),ui->MarkdownEditor, SLOT(selectAll()));

    QObject::connect(ui->actionRefresh,            SIGNAL(triggered()),ui->MarkdownPreview,SLOT(reload()));
    QObject::connect(ui->actionUpdateHTMLView,     SIGNAL(triggered()),this,               SLOT(UpdateHTMLView()));
    QObject::connect(ui->actionStopAutoPreview,    SIGNAL(toggled(bool)),this,             SLOT(toggleAutoPreview(bool)));

    QObject::connect(ui->actionInsertImage,        SIGNAL(triggered()),this,               SLOT(showInsertImageDialog()));
    QObject::connect(ui->actionInsertLink,         SIGNAL(triggered()),this,               SLOT(showInsertLinkDialog()));
    QObject::connect(ui->actionInsertTable,        SIGNAL(triggered()),this,               SLOT(showInsertTableDialog()));
    QObject::connect(ui->actionAbout,              SIGNAL(triggered()),this,               SLOT(showAboutDialog()));
    QObject::connect(ui->actionExportAsHTML,SIGNAL(triggered()),this,SLOT(showExportHTML()));

    QObject::connect(ui->actionMarkdownDocumentation,SIGNAL(triggered()),this,             SLOT(showMarkdownDocumentation()));
    QObject::connect(ui->actionExit,               SIGNAL(triggered()),this,               SLOT(close()));

    QObject::connect(ui->actionShrinkFont,         SIGNAL(triggered()),ui->MarkdownEditor, SLOT(zoomOut()));
    QObject::connect(ui->actionEnlargeFont,        SIGNAL(triggered()),ui->MarkdownEditor, SLOT(zoomIn()));

    QObject::connect(ui->actionVertical,           SIGNAL(changed()),this,                 SLOT(setVerticalOrientation()));
    QObject::connect(ui->actionHorizontal,         SIGNAL(changed()),this,                 SLOT(setHorizontalOrientation()));

    QObject::connect(this,                         SIGNAL(updateDocumentsListRequest(QString)),this,SLOT(updateDocumentsList(QString)));

    QObject::connect(ui->FileSystemTree,           SIGNAL(doubleClicked(QModelIndex)),this,SLOT(addFileFromFileSystemWidget(QModelIndex)));
    QObject::connect(ui->OpenDocumentsList,        SIGNAL(clicked(QModelIndex)),this,      SLOT(updateMarkdownEditor(QModelIndex)));
}

MarkEditWindow::~MarkEditWindow()
{
    saveWindowState();
    delete MarkEditSettings;
    delete ui;
    delete converter;
    delete Handler;
    delete Highlighter;
}

void MarkEditWindow::setOutput(QString html)

{
    if (this->autoPreview) {
        QString result = converter->convertMarkdown(html);
        ui->MarkdownPreview->setHtml(result);
    }
}

void MarkEditWindow::UpdateHTMLView()
{
    QString result = this->converter->convertMarkdown(ui->MarkdownEditor->toPlainText());
    ui->MarkdownPreview->setHtml(result);
}

void MarkEditWindow::copyAsHTML()
{
    QClipboard* clipBoard = qApp->clipboard();
    clipBoard->setText(this->converter->convertMarkdown(ui->MarkdownEditor->toPlainText()));
}

void MarkEditWindow::addBlankDocument()
{

}

void MarkEditWindow::openNewFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                       tr("Open File"),
                       QDir::homePath(),
                       "Markdown files "
                       "(*.markdown *.mdown *.mkdn *.md *.mkd *.mdwn *.mdtxt *.mdtext *.text)"
                                                    );

    if (!this->Handler->contains(filePath)) {
    this->Handler->addFile(filePath);
    emit updateDocumentsListRequest(QUrl(filePath).fileName());
    } else return;
}

void MarkEditWindow::saveCurrentFile()
{
    //this->Handler->at(ui->OpenDocumentsList->currentIndex().row())->saveToTemporary(ui->MarkdownEditor->toPlainText());
    //this->Handler->at(ui->OpenDocumentsList->currentIndex().row())->saveFile();
    int index = ui->OpenDocumentsList->currentIndex().row();
    this->Handler->commitFile(index);
}

void MarkEditWindow::stageCurrentFile()
{
    int index = ui->OpenDocumentsList->currentIndex().row();
    QByteArray content = ui->MarkdownEditor->toPlainText().toUtf8();
    this->Handler->stageFile(index,content);
}

void MarkEditWindow::saveCurrentFileAs()
{
    QString saveAsPath = QFileDialog::getSaveFileName(
                this,
                tr("Save File As"),
                QDir::homePath(),
                "Markdown files "
                "(*.markdown *.mdown *.mkdn *.md *.mkd *.mdwn *.mdtxt *.mdtext *.text)"
                );

    if(saveAsPath.isEmpty())
        return;

    QFile* saveAsFile = new QFile(saveAsPath);
    saveAsFile->open(QIODevice::WriteOnly | QIODevice::Text);
    if (saveAsFile->isWritable()) {
        saveAsFile->write(ui->MarkdownEditor->toPlainText().toUtf8());
    } else {
        QMessageBox::information(this,"Error writing to file","Cannot write to the choosen output file, do you have write permission to it?");
    }

    saveAsFile->close();
    delete saveAsFile;
}

void MarkEditWindow::closeCurrentFile()
{
    this->Handler->removeFile(ui->OpenDocumentsList->currentIndex().row());
    this->documentsList.removeAt(ui->OpenDocumentsList->currentIndex().row());
    this->documentsListModel->setStringList(this->documentsList);
    ui->MarkdownEditor->clear();
}

void MarkEditWindow::updateDocumentsList(QString docName)
{
    this->documentsList.append(docName);
    this->documentsListModel->setStringList(this->documentsList);
    ui->OpenDocumentsList->setModel(this->documentsListModel);
}

void MarkEditWindow::updateMarkdownEditor(QModelIndex docListIndex)
{
    ui->MarkdownEditor->setPlainText(this->Handler->readFile(docListIndex.row()));
    //updateWindowTitle(this->documentsList.at(docListIndex.row()),false);
}

void MarkEditWindow::addFileFromFileSystemWidget(QModelIndex model)
{
    QString fileName = this->fileSystemModel->filePath(model);
    if (!this->Handler->contains(fileName)) {
    this->Handler->addFile(fileName);
    emit updateDocumentsListRequest(QUrl(fileName).fileName());
    } else
        return;
}


void MarkEditWindow::initFileSystemModel()
{
    fileSystemModel = new QFileSystemModel(this);
    ui->FileSystemTree->setModel(this->fileSystemModel);
    fileSystemModel->setRootPath(QDir::homePath());
    ui->FileSystemTree->setRootIndex(fileSystemModel->index(QDir::homePath()));
    ui->FileSystemTree->hideColumn(1); //remove unwanted columns
    ui->FileSystemTree->hideColumn(2);
    ui->FileSystemTree->hideColumn(3);
    fileSystemFilters << "*.markdown" << "*.mdown" << "*.mkdn" << "*.md" << "*.mkd"
                         << "*.mdwn" << "*.mdtxt" << "*.mdtext" << "*.text";
    fileSystemModel->setNameFilters(fileSystemFilters);
    fileSystemModel->setNameFilterDisables(false);
}

void MarkEditWindow::initDocumentsListModel()
{
    documentsListModel = new QStringListModel(this);
    //documentsListModel->setStringList(documentsList); QStringList still empty, do nothing
    ui->OpenDocumentsList->setModel(documentsListModel);
}

void MarkEditWindow::on_MarkdownEditor_textChanged()
{
    emit sourceChanged(ui->MarkdownEditor->toPlainText());
    if(ui->OpenDocumentsList->currentIndex().row() > -1)
        stageCurrentFile();
    //this->Handler->at(ui->OpenDocumentsList->currentIndex().row())->saveToTemporary(ui->MarkdownEditor->toPlainText());
}

void MarkEditWindow::fileSystemVisibility(bool visible)
{
    if (visible) {
        ui->FileSystemTree->setVisible(true);
    } else {
        ui->FileSystemTree->setHidden(true);
    }
}

void MarkEditWindow::documentListVisibility(bool visible)
{
    if (visible) {
        ui->OpenDocumentsList->setVisible(true);
    } else {
        ui->OpenDocumentsList->setHidden(true);
    }
}

void MarkEditWindow::markdownEditorVisibility(bool visible)
{
    if (visible) {
        ui->MarkdownEditor->setVisible(true);
    } else {
        ui->MarkdownEditor->setHidden(true);
    }
}

void MarkEditWindow::HTMLPreviewVisibility(bool visible)
{
    if (visible) {
        ui->MarkdownPreview->setVisible(true);
    } else {
        ui->MarkdownPreview->setHidden(true);
    }
}

void MarkEditWindow::setHorizontalOrientation()
{
    ui->Editor_Preview_Splitter->setOrientation(Qt::Horizontal);
}

void MarkEditWindow::setVerticalOrientation()
{
    ui->Editor_Preview_Splitter->setOrientation(Qt::Vertical);
}

void MarkEditWindow::insertFormatBold()
{
    QTextCursor selectionBegin(ui->MarkdownEditor->document());
    selectionBegin.setPosition(ui->MarkdownEditor->textCursor().anchor());

    QTextCursor selectionEnd(ui->MarkdownEditor->document());
    selectionEnd.setPosition(ui->MarkdownEditor->textCursor().position());

    //only of there is selected text
    if (selectionBegin.position() != selectionEnd.position()) {
    selectionBegin.insertText("**");
    selectionEnd.insertText("**");
    }
}

void MarkEditWindow::insertFormatItalic()
{
    QTextCursor selectionBegin(ui->MarkdownEditor->document());
    selectionBegin.setPosition(ui->MarkdownEditor->textCursor().anchor());

    QTextCursor selectionEnd(ui->MarkdownEditor->document());
    selectionEnd.setPosition(ui->MarkdownEditor->textCursor().position());

    //only of there is selected text
    if (selectionBegin.position() != selectionEnd.position()) {
    selectionBegin.insertText("_");
    selectionEnd.insertText("_");
    }
}

void MarkEditWindow::insertFormatStrikethrough()
{
    QTextCursor selectionBegin(ui->MarkdownEditor->document());
    selectionBegin.setPosition(ui->MarkdownEditor->textCursor().anchor());

    QTextCursor selectionEnd(ui->MarkdownEditor->document());
    selectionEnd.setPosition(ui->MarkdownEditor->textCursor().position());

    //only of there is selected text
    if (selectionBegin.position() != selectionEnd.position()) {
    selectionBegin.insertText("~~");
    selectionEnd.insertText("~~");
    }
}

void MarkEditWindow::insertHeadingOne()
{
    QTextCursor headingInsertCursor(ui->MarkdownEditor->document());

    if (!headingInsertCursor.hasSelection()) {
        headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().selectionStart());
        headingInsertCursor.beginEditBlock();
        headingInsertCursor.insertText("#");
        headingInsertCursor.endEditBlock();
    } else {
        headingInsertCursor.beginEditBlock();
        headingInsertCursor.movePosition(QTextCursor::EndOfLine);
        headingInsertCursor.insertText(QString('\n'));
        headingInsertCursor.insertText("#");
        headingInsertCursor.endEditBlock();
    }/*
    headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headingInsertCursor.beginEditBlock();
    headingInsertCursor.insertText("#");
    headingInsertCursor.endEditBlock();*/
}

void MarkEditWindow::insertHeadingTwo()
{
    QTextCursor headingInsertCursor(ui->MarkdownEditor->document());
    headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headingInsertCursor.beginEditBlock();
    headingInsertCursor.insertText("##");
    headingInsertCursor.endEditBlock();
}

void MarkEditWindow::insertHeadingThree()
{
    QTextCursor headingInsertCursor(ui->MarkdownEditor->document());
    headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headingInsertCursor.beginEditBlock();
    headingInsertCursor.insertText("###");
    headingInsertCursor.endEditBlock();
}

void MarkEditWindow::insertHeadingFour()
{
    QTextCursor headingInsertCursor(ui->MarkdownEditor->document());
    headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headingInsertCursor.beginEditBlock();
    headingInsertCursor.insertText("####");
    headingInsertCursor.endEditBlock();
}

void MarkEditWindow::insertHeadingFive()
{
    QTextCursor headingInsertCursor(ui->MarkdownEditor->document());
    headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headingInsertCursor.beginEditBlock();
    headingInsertCursor.insertText("#####");
    headingInsertCursor.endEditBlock();
}

void MarkEditWindow::insertHeadingSix()
{
    QTextCursor headingInsertCursor(ui->MarkdownEditor->document());
    headingInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headingInsertCursor.beginEditBlock();
    headingInsertCursor.insertText("######");
    headingInsertCursor.endEditBlock();
}

void MarkEditWindow::insertBlockquote()
{
    QTextCursor headerInsertCursor(ui->MarkdownEditor->document());
    headerInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headerInsertCursor.beginEditBlock();
    headerInsertCursor.insertText(">");
    headerInsertCursor.endEditBlock();
}

void MarkEditWindow::insertCode()
{
    QTextCursor headerInsertCursor(ui->MarkdownEditor->document());
    headerInsertCursor.setPosition(ui->MarkdownEditor->textCursor().position());
    headerInsertCursor.beginEditBlock();
    headerInsertCursor.insertText("\t");
    headerInsertCursor.endEditBlock();
}

void MarkEditWindow::toggleAutoPreview(bool arg1)
{
    this->autoPreview = !arg1;
}

void MarkEditWindow::showAboutDialog()
{
    AboutDialog *About = new AboutDialog(this);
    if (About->exec() == QDialog::Accepted){

    }
    delete About;
}

void MarkEditWindow::showInsertImageDialog()
{
    InsertImageDialog* ImageDialog = new InsertImageDialog(this);
    if (ImageDialog->exec() == QDialog::Accepted) {
        if (!ImageDialog->getReferenceType()) {
            ui->MarkdownEditor->insertPlainText(QString("![" +
                                                      ImageDialog->getImageAlt() +
                                                      "](" +
                                                      ImageDialog->getImageURL() +
                                                      "\"" +
                                                      ImageDialog->getImageTooltip() +
                                                      "\")"
                                                      ));
        } else if(ImageDialog->getReferenceType())
        {
            ui->MarkdownEditor->insertPlainText(QString("![" +
                                                      ImageDialog->getImageAlt() +
                                                      "][" +
                                                      ImageDialog->getImageReferenceName() +
                                                      "]\n"
                                              ));

            ui->MarkdownEditor->insertPlainText(QString("[" +
                                                      ImageDialog->getImageReferenceName() +
                                                      "]: " +
                                                      ImageDialog->getImageURL() +
                                                      " \"" +
                                                      ImageDialog->getImageAlt() +
                                                      "\""
                                              ));
        }
    }
    delete ImageDialog;
}

void MarkEditWindow::showInsertLinkDialog()
{
    InsertLinkDialog* LinkDialog = new InsertLinkDialog(this);
    if (LinkDialog->exec() == QDialog::Accepted) {
        if (!LinkDialog->getReferenceType()) {
        ui->MarkdownEditor->insertPlainText(QString("[" +
                                                  LinkDialog->getLinkLabel() +
                                                  "](" +
                                                  LinkDialog->getLinkURL() +
                                                  ")")
                                          );
        } else {
            ui->MarkdownEditor->insertPlainText(QString("[" +
                                                        LinkDialog->getLinkLabel() +
                                                        "][" +
                                                        LinkDialog->getReferenceName()+
                                                        "]\n"+
                                                        "["+
                                                        LinkDialog->getReferenceName()+
                                                        "]:" +
                                                        LinkDialog->getLinkURL()));
        }
    }
    delete LinkDialog;
}

void MarkEditWindow::showInsertTableDialog()
{
    InsertTableDialog* TableDialog = new InsertTableDialog(this);
    if (TableDialog->exec() == QDialog::Accepted) {
        ui->MarkdownEditor->appendPlainText(TableDialog->table());
    }
    delete TableDialog;
}

void MarkEditWindow::showMarkdownDocumentation()
{
    MarkdownDocumentation* DocumentationDialog = new MarkdownDocumentation(this);
    if (DocumentationDialog->exec() == QDialog::Accepted) {

    }
    delete DocumentationDialog;
}

void MarkEditWindow::showExportPDF()
{
    ExportPDF* ExportDialog = new ExportPDF(this);
    if (ExportDialog->exec() == QDialog::Accepted) {

    }
    delete ExportDialog;
}

void MarkEditWindow::showExportHTML()
{
    ExportHTML* ExportDialog = new ExportHTML(this);
    if (ExportDialog->exec() == QDialog::Accepted) {
        ExportDialog->setHtml(converter->convertMarkdown(ui->MarkdownEditor->toPlainText()));
        ExportDialog->exportHTML();
    }
    delete ExportDialog;
}

void MarkEditWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete && ui->OpenDocumentsList->currentIndex().row() != -1) {
        this->Handler->removeFile(ui->OpenDocumentsList->currentIndex().row());
        this->documentsList.removeAt(ui->OpenDocumentsList->currentIndex().row());
        this->documentsListModel->setStringList(this->documentsList);
        ui->OpenDocumentsList->scrollToTop();
        ui->MarkdownEditor->clear();
        updateWindowTitle("",true);
    }
}

void MarkEditWindow::saveWindowState()
{
    this->MarkEditSettings->setValue("editor-width",QVariant(ui->MarkdownEditor->width()));
    this->MarkEditSettings->setValue("preview-width",QVariant(ui->MarkdownPreview->width()));

    this->MarkEditSettings->setValue("window-position",QVariant(this->pos()));
    this->MarkEditSettings->setValue("editor-visible",QVariant(ui->MarkdownEditor->isVisible()));
    this->MarkEditSettings->setValue("preview-visible",QVariant(ui->MarkdownPreview->isVisible()));
    this->MarkEditSettings->setValue("filesystem-visible",QVariant(ui->FileSystemTree->isVisible()));
    this->MarkEditSettings->setValue("opendocuments-visible",QVariant(ui->OpenDocumentsList->isVisible()));

}

void MarkEditWindow::updateWindowTitle(const QString &value, bool reset = false)
{
    if(reset)
        this->setWindowTitle("MarkEdit");
    else
        this->setWindowTitle(QString("%1 - MarkEdit").arg(value));
}

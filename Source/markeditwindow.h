#ifndef MARKEDITWINDOW_H
#define MARKEDITWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QVector>
#include <QFileDialog>
#include <QActionGroup>
#include <QSettings>
#include <QClipboard>
#include "Core/MarkdownConverter/markdownconverter.h"
#include "Core/DocumentsHandler/documentshandler.h"
#include "../Plugins/MarkdownHighlighter/markdownhighlighter.h"

namespace Ui {
class MarkEditWindow;
}

class MarkEditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarkEditWindow(QWidget *parent = 0);
    ~MarkEditWindow();

private:
    Ui::MarkEditWindow *ui;
    QActionGroup* orientationGroup;
    MarkdownHighlighter *Highlighter;
    DocumentsHandler* Handler;
    QFileSystemModel* fileSystemModel;
    QStringListModel* documentsListModel;
    QStringList documentsList;
    QStringList fileSystemFilters;

    MarkdownConverter *converter;
    bool autoPreview;

    QSettings* MarkEditSettings;

    void initFileSystemModel();
    void initDocumentsListModel();
    void saveWindowState();

signals:
    void sourceChanged(QString);
    void addFileRequest(QString);
    void saveFileRequest(int index);
    void removeFileRequest(int index);
    void updateDocumentsListRequest(QString);

private slots:
    void updateWindowTitle(const QString &value, bool reset);

    void UpdateHTMLView();
    void copyAsHTML();

    void setHorizontalOrientation();
    void setVerticalOrientation();

    void setOutput(QString html);
    void on_MarkdownEditor_textChanged();

    void addBlankDocument();
    void openNewFile();
    void saveCurrentFile();
    void stageCurrentFile();
    void saveCurrentFileAs();
    void closeCurrentFile();
    void updateDocumentsList(QString docName);
    void updateMarkdownEditor(QModelIndex docListIndex);
    void addFileFromFileSystemWidget(QModelIndex model);

    void fileSystemVisibility(bool visible);
    void documentListVisibility(bool visible);
    void markdownEditorVisibility(bool visible);
    void HTMLPreviewVisibility(bool visible);

    void insertFormatBold();
    void insertFormatItalic();
    void insertFormatStrikethrough();

    void insertHeadingOne();
    void insertHeadingTwo();
    void insertHeadingThree();
    void insertHeadingFour();
    void insertHeadingFive();
    void insertHeadingSix();

    void insertBlockquote();
    void insertCode();

    void toggleAutoPreview(bool arg1);

    void showAboutDialog();
    void showInsertImageDialog();
    void showInsertLinkDialog();
    void showInsertTableDialog();
    void showMarkdownDocumentation();
    void showExportPDF();
    void showExportHTML();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MARKEDITWINDOW_H

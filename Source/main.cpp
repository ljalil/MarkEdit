#include "markeditwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationDomain("abdeljalil");
    app.setApplicationName("MarkEdit");
    MarkEditWindow MarkEdit;
    MarkEdit.setWindowState(Qt::WindowMaximized);
    MarkEdit.setWindowTitle("MarkEdit");
    MarkEdit.show();

    return app.exec();
}

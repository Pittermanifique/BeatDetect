#include "mainwindow.h"
#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QApplication app(argc, argv);
    // Charge l’icône interne (depuis un .qrc ou un chemin absolu)
    app.setWindowIcon(QIcon("icone.ico"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include "foldersync.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FolderSync w;
    w.show();

    return a.exec();
}

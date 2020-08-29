#include <QApplication>

#include "main_window.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::instance();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

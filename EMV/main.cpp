#include <QApplication>

#include "emv.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("ISTI");
    QCoreApplication::setOrganizationDomain("ISTI.com");
    QCoreApplication::setApplicationName("EMV");

    EMV w;

    w.showMaximized();

    return a.exec();
}

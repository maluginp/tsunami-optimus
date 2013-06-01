#include <QApplication>
#include "deviceworkspace.h"
#include <QDebug>
#include "core/tdblayer.h"

#include "gui/formweightconst.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DeviceWorkspace w;
    w.show();
    return a.exec();
}

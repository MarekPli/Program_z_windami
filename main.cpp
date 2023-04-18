
#include "widget.h"

#include <QApplication>

enum directionKind {
    up,
    down,
    staying,
    boarding,
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

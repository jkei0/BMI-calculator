// Joni Keinänen
// 267144
// joni.keinanen@student.tut.fi

#include "painoindeksilaskin.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painoindeksilaskin w;
    w.show();

    return a.exec();
}

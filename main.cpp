#include "salario.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salario w;
    w.show();
    return a.exec();
}

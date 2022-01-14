#include "salario.h"
#include "obrero.h"
#include "controlador.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salario w;
    w.show();



    /* COMPROBACION

    // Creacion de Objs
    // Obrero *objObrero1 =new Obrero("Juan",47,TipoJornada::Vespertina);

    qDebug() << objObrero1->nombre() << objObrero1->horas();
    switch (objObrero1->jornada()){  // Clasificación de la jornada
    case TipoJornada::Matutina :
        qDebug() << "matutino";
        break;

    case TipoJornada::Vespertina:
        qDebug() << "Vespertina";
        break;

    case TipoJornada::Nocturna :
        qDebug() << "Nocturna";
        break;
    }*/

    Controlador *obj=new Controlador();
    obj->agregarObrero("Juan",40,TipoJornada::Matutina);
    if(obj->calcularSalario()){
        qDebug() << obj->obrero()->tostring();
    }else{
        qDebug() << "No se pudo realizar el calculo de salrios...";
    }

    return a.exec();
}

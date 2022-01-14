#include "salario.h"
#include "ui_salario.h"

Salario::Salario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salario)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
}

Salario::~Salario()
{
    delete ui;
}


void Salario::on_cmdCalcular_clicked()
{
    // Obtener datos de IU
    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;

    if(ui->inMatutina->isChecked()){
        jornada = TipoJornada::Matutina;
    }else if (ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }

    // Agregar datos al controlador
    m_controlador->agregarObrero(nombre,horas,jornada);
    // Calcular
    if(m_controlador->calcularSalario()){
        ui->outResultado->appendPlainText(m_controlador->obrero()->tostring());
    }else{

    }
}


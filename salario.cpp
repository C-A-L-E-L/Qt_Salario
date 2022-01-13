#include "salario.h"
#include "ui_salario.h"

Salario::Salario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salario)
{
    ui->setupUi(this);
}

Salario::~Salario()
{
    delete ui;
}


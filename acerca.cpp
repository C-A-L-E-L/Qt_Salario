#include "acerca.h"
#include "ui_acerca.h"

Acerca::Acerca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acerca)
{
    ui->setupUi(this);
    m_valor = 5;
}

Acerca::~Acerca()
{
    delete ui;
}

void Acerca::setVersion(const QString &newVersion)
{
    m_version = newVersion;
    this->ui->lblNombre->setText("Salarios " + m_version);
}

int Acerca::valor() const
{
    return m_valor;
}

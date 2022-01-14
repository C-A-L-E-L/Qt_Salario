#ifndef SALARIO_H
#define SALARIO_H

#include <QMainWindow>
#include "controlador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Salario; }
QT_END_NAMESPACE

class Salario : public QMainWindow
{
    Q_OBJECT

public:
    Salario(QWidget *parent = nullptr);
    ~Salario();

private slots:
    void on_cmdCalcular_clicked();

private:
    Ui::Salario *ui;
    Controlador *m_controlador;
};
#endif // SALARIO_H

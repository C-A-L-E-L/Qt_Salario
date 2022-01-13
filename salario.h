#ifndef SALARIO_H
#define SALARIO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Salario; }
QT_END_NAMESPACE

class Salario : public QMainWindow
{
    Q_OBJECT

public:
    Salario(QWidget *parent = nullptr);
    ~Salario();

private:
    Ui::Salario *ui;
};
#endif // SALARIO_H

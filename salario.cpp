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
    calcular();
}

void Salario::limpiar()
{
    // Limpiar las entras [valores por defecto]
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    // Regresa el cursor
    ui->inNombre->setFocus();
    // Limpiar las salidas de totales
    ui->outTotalB->setText("0");
    ui->outTotalIESS->setText("0");
    ui->outTotalN->setText("0");
}

void Salario::calcular()
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

    // Validar datos correctos y mostrar mensaje de advertencia 2 formas
    if(nombre == ""  || horas == 0){
        /*QMessageBox msgBox; // [1]
        msgBox.setText("El nombre o el numero de horas esta vacio");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();*/

        QMessageBox::warning(this,
                             "ADVERTENCIA",
                             "El nombre o el numero de horas esta vacio.a"); // [2]
        return;
    }

    // Agregar datos al controlador
    m_controlador->agregarObrero(nombre,horas,jornada);
    // Calcular
    if(m_controlador->calcularSalario()){
        // Muestra los resultados del calculo salarial
        ui->outResultado->appendPlainText(m_controlador->obrero()->tostring());
        // Limiar interfaz
        limpiar();
        // Mostrar mensaje por 5 seg en la barra de estado
        ui->statusbar->showMessage("Calculo procesado para " + nombre,5000);
    }else{
        QMessageBox::critical(this,
                              "ERROR",
                              "Error al calcular el salario.");
        return;
    }
}

void Salario::guardar()
{
    // Abrir cuadro de dialogo para selecionar nombre y ubicación del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "GUARDAR ARCHIVO", // Nombre
                                                         QDir::home().absolutePath(), // Donde empiece el cuadro de dialogo
                                                         "Archivos de salario (*.slr)"); // [Filtro] tipo de documento
    // Crear un obj QFile
    QFile archivo(nombreArchivo);
    // Abrirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear stream [Flujo de texto]
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outResultado->toPlainText();
        // MOstrar por 5 seg que todo salio bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo,5000);
    }else{
        // Mensaje de error si no s epeude abrir el archivo
        QMessageBox::warning(this,
                             "GUARDAR",
                             "No se logro salvar el archivo");
    }
    // Cerrar el archivo
    archivo.close();
}

void Salario::abrir()
{
    // Abrir cuadro de dialogo para selecionar nombre y ubicación del archivo
    QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                         "ABRIR ARCHIVO", // Nombre
                                                         QDir::home().absolutePath(), // Donde empiece el cuadro de dialogo
                                                         "Archivos de salario (*.slr)"); // [Filtro] tipo de documento
    // Crear un obj QFile
    QFile archivo(nombreArchivo);
    // Abrirlo para lectura
    if(archivo.open(QFile::ReadOnly)){
        // Crear stream [Flujo de texto]
        QTextStream entrada(&archivo);
        // Leer  rodo el contenido del archivo
        QString datos = entrada.readAll();
        // Cargar el contenido al area texto
        ui->outResultado->clear();
        ui->outResultado->setPlainText(datos);
        // MOstrar por 5 seg que todo salio bien
        ui->statusbar->showMessage("Datos leidos desde " + nombreArchivo,5000);
    }else{
        // Mensaje de error si no s epeude abrir el archivo
        QMessageBox::warning(this,
                             "ABRIR ARCHIVOS",
                             "No se puede abrir el archivo");
    }
    // Cerrar el archivo
    archivo.close();
}

void Salario::on_actionCalcular_triggered()
{
    calcular();
    ui->outTotalB->setText(QString::number(m_controlador->m_totalBruto,'f',2));
    ui->outTotalIESS->setText(QString::number(m_controlador->m_totalIESS));
    ui->outTotalN->setText(QString::number(m_controlador->m_totalNeto,'f',2));
}

void Salario::on_actionGuardar_triggered()
{
    guardar();
}

void Salario::on_actionNuevo_triggered()
{
    limpiar();
    ui->outResultado->clear();
}

void Salario::on_actionAbrir_triggered()
{
    abrir();
}

void Salario::on_actionAcerca_de_Salario_triggered()
{
    // Crear un obj de la ventama que deseamos invocar
    Acerca *dialogo = new Acerca(this);
    // Enviar parametro a la ventana
    dialogo->setVersion(VERSION);
    // Mostrar la ventana [dialogo->show();]
    dialogo->exec();
    // Obtener datos de la ventana
    qDebug() << dialogo->valor();
}

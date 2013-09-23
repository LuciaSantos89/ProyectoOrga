#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    crearActions();
    agregar();
    activardesactivarMenus(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::crearActions(){
    //Menu Archivo
    actionNuevoArchivo= new QAction("&Nuevo",this);
    actionNuevoArchivo->setShortcut(tr("Ctrl+N"));
    connect(actionNuevoArchivo,SIGNAL(triggered()),this,SLOT(nuevoArchivo()));

    actionAbrirArchivo= new QAction("&Abrir",this);
    actionAbrirArchivo->setShortcut(tr("Ctrl+O"));
    connect(actionAbrirArchivo,SIGNAL(triggered()),this,SLOT(abrirArchivo()));

    actionGuardarArchivo= new QAction("&Guardar",this);
    actionGuardarArchivo->setShortcut(tr("Ctrl+S"));
    connect(actionGuardarArchivo,SIGNAL(triggered()),this,SLOT(guardarArchivo()));

    actionImprimirArchivo= new QAction("&Imprimir",this);
    actionImprimirArchivo->setShortcut(tr("Ctrl+P"));
    connect(actionImprimirArchivo,SIGNAL(triggered()),this,SLOT(imprimirArchivo()));

    actionCerrarArchivo= new QAction("&Cerrar",this);
    actionCerrarArchivo->setShortcut(tr("Ctrl+C"));
    connect(actionCerrarArchivo,SIGNAL(triggered()),this,SLOT(cerrarArchivo()));

    actionSalirArchivo= new QAction("&Salir",this);
    actionSalirArchivo->setShortcut(tr("Ctrl+X"));
    connect(actionSalirArchivo,SIGNAL(triggered()),this,SLOT(salir()));

    //Menu Campo
    actionCrearCampo= new QAction("&Crear Campo",this);
    actionCrearCampo->setShortcut(tr("Ctrl+C"));
    connect(actionCrearCampo,SIGNAL(triggered()),this,SLOT(crearCampo()));

    actionListarCampo= new QAction("&Listar Campos",this);
    actionListarCampo->setShortcut(tr("Ctrl+L"));
    connect(actionListarCampo,SIGNAL(triggered()),this,SLOT(listarCampo()));

    //Menu Registro
    actionIntroducirRegistro=new QAction("Introducir Registro",this);
    connect(actionIntroducirRegistro,SIGNAL(triggered()),this,SLOT(introducirRegistro()));

    actionBuscarRegistro=new QAction("Buscar Registro",this);
    connect(actionBuscarRegistro,SIGNAL(triggered()),this,SLOT(buscarRegistro()));

    actionBorrarRegistro=new QAction("Borrar Registro",this);
    connect(actionBorrarRegistro,SIGNAL(triggered()),this,SLOT(borrarRegistro()));

    actionListarRegistro=new QAction("Listar Registro",this);
    connect(actionListarRegistro,SIGNAL(triggered()),this,SLOT(listarRegistro()));

    //Menu Indices
    actionCrearIndiceSimple=new QAction("Crear Indice Simple",this);
    connect(actionCrearIndiceSimple,SIGNAL(triggered()),this,SLOT(crearIndiceSimple()));

    actionCrearArbolB=new QAction("Crear Arbol B",this);
    connect(actionCrearArbolB,SIGNAL(triggered()),this,SLOT(crearArbolB()));

    actionReindexar=new QAction("Reindexar",this);
    connect(actionReindexar,SIGNAL(triggered()),this,SLOT(reindexar()));

    //Menu Utilidades
    actionImportarXML=new QAction("Impotar XML",this);
    connect(actionImportarXML,SIGNAL(triggered()),this,SLOT(importarXML()));

    actionExportarXML=new QAction("Exportar XML",this);
    connect(actionExportarXML,SIGNAL(triggered()),this,SLOT(exportarXML()));

    actionImportarJSON=new QAction("Impotar JSON",this);
    connect(actionImportarJSON,SIGNAL(triggered()),this,SLOT(importarJSON()));

    actionExportarJSON=new QAction("Exportar JSON",this);
    connect(actionExportarJSON,SIGNAL(triggered()),this,SLOT(exportarJSON()));

}

void MainWindow::agregar(){

    //Ventana Principal
    this->setMinimumSize(700, 300);
    this->setWindowTitle("Proyecto - Lusilla");

    //Menu Archivo
    mArchivo=menuBar()->addMenu("&Archivo");
    mArchivo->addAction(actionNuevoArchivo);
    mArchivo->addAction(actionAbrirArchivo);
    mArchivo->addAction(actionGuardarArchivo);
    mArchivo->addAction(actionImprimirArchivo);
    mArchivo->addAction(actionCerrarArchivo);
    mArchivo->addAction(actionSalirArchivo);

    //Menu Campo
    mCampo=menuBar()->addMenu("&Campo");
    mCampo->addAction(actionCrearCampo);
    mCampo->addAction(actionListarCampo);

    //Menu Registro
    mRegistro=menuBar()->addMenu("&Registro");
    mRegistro->addAction(actionIntroducirRegistro);
    mRegistro->addAction(actionBorrarRegistro);
    mRegistro->addAction(actionBuscarRegistro);
    mRegistro->addAction(actionListarRegistro);

    //Menu Indices
    mIndices=menuBar()->addMenu("&Indices");
    mIndices->addAction(actionCrearIndiceSimple);
    mIndices->addAction(actionCrearArbolB);
    mIndices->addAction(actionReindexar);

    //Menu Utilidades
    mUtilidades=menuBar()->addMenu("&Utilidades");
    mUtilidades->addAction(actionImportarXML);
    mUtilidades->addAction(actionExportarXML);
    mUtilidades->addAction(actionImportarJSON);
    mUtilidades->addAction(actionExportarJSON);

    //Dialogo Crear Campo
    dialogcrearCampo=new QDialog(this,Qt::Dialog);
    dialogcrearCampo->hide();
    dialogcrearCampo->setMinimumSize(350,350);
    dialogcrearCampo->setWindowTitle("Crear Campo");
    dialogcrearCampo->setModal(true);
    dialogcrearCampo->setWindowModality(Qt::WindowModal);

    labelCampo=new QLabel("Nombre",dialogcrearCampo);
    labelCampo->move(20,50);
    lineNombreCampo=new QLineEdit(dialogcrearCampo);
    lineNombreCampo->move(100,50);
    lineNombreCampo->setMinimumWidth(100);

    labelCampo=new QLabel("Tipo",dialogcrearCampo);
    labelCampo->move(20,100);
    comboTipoCampo= new QComboBox(dialogcrearCampo);
    comboTipoCampo->move(100,100);
    QStringList tipos;
    tipos<<"Cadena"<<"Entero"<<"Real";
    comboTipoCampo->addItems(tipos);
    connect(comboTipoCampo,SIGNAL(currentIndexChanged(int)),this,SLOT(cambiarTipoCampo()));

    labelCampo=new QLabel("Longitud",dialogcrearCampo);
    labelCampo->move(20,150);
    spinLongitud=new QSpinBox(dialogcrearCampo);
    spinLongitud->move(100,150);
    spinLongitud->setValue(1);

    labelCampo=new QLabel("Decimal",dialogcrearCampo);
    labelCampo->move(20,200);
    spinDecimal=new QSpinBox(dialogcrearCampo);
    spinDecimal->move(100,200);
    spinDecimal->setEnabled(false);

    labelCampo=new QLabel("Llave",dialogcrearCampo);
    labelCampo->move(20,250);
    checkLlave=new QCheckBox(dialogcrearCampo);
    checkLlave->move(100,250);

    aceptarcrearCampo=new QPushButton("Aceptar",dialogcrearCampo);
    aceptarcrearCampo->move(50,300);
    connect(aceptarcrearCampo,SIGNAL(clicked()),this,SLOT(click_aceptarCrearCampo()));

    cancelarcrearCampo=new QPushButton("Cancelar",dialogcrearCampo);
    cancelarcrearCampo->move(300,300);
    connect(cancelarcrearCampo,SIGNAL(clicked()),this,SLOT(click_cancelarCampo()));

    //Dialogo Listar Campos
    dialoglistarCampo = new QDialog(this,Qt::Dialog);
    dialoglistarCampo->hide();
    dialoglistarCampo->setMinimumSize(550,350);
    dialoglistarCampo->setWindowTitle("Listar Campos");
    dialoglistarCampo->setModal(true);
    dialoglistarCampo->setWindowModality(Qt::WindowModal);

    aceptarlistarCampo=new QPushButton("Aceptar",dialoglistarCampo);
    aceptarlistarCampo->move(450,320);
    connect(aceptarlistarCampo,SIGNAL(clicked()),this,SLOT(click_aceptarListarCampo()));

    //Tabla Listar Campos
    tableCampo= new QTableWidget(0,5,dialoglistarCampo);
    QStringList titulo;
    titulo << "Nombre" << "Tipo"<<"Longitud"<<"Decimal"<<"Llave";
    tableCampo->setHorizontalHeaderLabels(titulo);
    tableCampo->setMinimumSize(550,250);
    tableCampo->move(50,50);
    tableCampo->setColumnWidth(0,130);

}

//funciones Menu Archivo
void MainWindow::nuevoArchivo(){
    activardesactivarMenus(true);
    archivo=new TDARecordFile();
    header=new Header();
    indices= new Index();
    registros.clear();
    campos.clear();
    registro.clear();
    regIntroducido=false;
}

void MainWindow::abrirArchivo(){
    QString nombreArchivo = QFileDialog::getOpenFileName(this,tr("Abrir Documento"),QDir::currentPath(),"Lusilla (*.lsll)");
    if( !nombreArchivo.isNull() ){
        activardesactivarMenus(true);
        archivo=new TDARecordFile();
        header=new Header();
        campos.clear();
        registros.clear();
        registro.clear();
        fn = nombreArchivo.toStdString();
        archivo->open(fn,ios_base::out | ios_base::in);
        header->recuperarHeader(archivo);
        campos=header->getCampos();
        indices= new Index(archivo->abrirIndices(fn));
        int longitudTotal=0;
        for(unsigned int i=0; i<campos.size();i++){
            longitudTotal+=campos.at(i)->getLongitud();
        }
        archivo->getAvaillist(longitudTotal);
    }
}

void MainWindow::guardarArchivo(){
    if(!regIntroducido){
        QString nombreArchivo = QFileDialog::getSaveFileName(this,tr("Guardar Documento"),QDir::currentPath(),"Lusilla (*.lsll)");
        if(!nombreArchivo.isNull()){
            fn = nombreArchivo.toStdString()+".lsll";
            archivo->open(fn,ios_base::out);
            header->crearHeader(campos);
            header->guardarHeader(archivo);
        }
    }
}

void MainWindow::imprimirArchivo(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}

void MainWindow::cerrarArchivo(){
    if(archivo->isOpen()){
        archivo->guardarIndices(indices,fn);
        archivo->flush();
        archivo->close();
    }
    activardesactivarMenus(false);
}

void MainWindow::salir(){
    this->cerrarArchivo();
    this->close();
}

//Funcines Menu Campo
void MainWindow::crearCampo(){
    if(regIntroducido){
        errorM=new QErrorMessage(dialogcrearCampo);
        errorM->showMessage("Ya no puede crear campos");
        return;
    }
    dialogcrearCampo->show();
}

void MainWindow::listarCampo(){
    if(campos.size()==0)
        return;
        tableCampo->setRowCount(campos.size());
        string s="";
        stringstream tmp;
        for (unsigned int i = 0; i < campos.size(); i++) {
            s= campos.at(i)->getNombre();
            itemTableCampo= new QTableWidgetItem(0);
            itemTableCampo->setText(s.c_str());
            tableCampo->setItem(i,0,itemTableCampo);

            int tipo=campos.at(i)->getTipo();
            if(tipo==0)
                tmp<<"Cadena";
            if(tipo==1)
                tmp<<"Entero";
            if(tipo==2)
                tmp<<"Real";
            s=tmp.str();
            itemTableCampo= new QTableWidgetItem(0);
            itemTableCampo->setText(s.c_str());
            tableCampo->setItem(i,1,itemTableCampo);
            tmp.str("");

            tmp<<campos.at(i)->getLongitud();
            s=tmp.str();
            itemTableCampo= new QTableWidgetItem(0);
            itemTableCampo->setText(s.c_str());
            tableCampo->setItem(i,2,itemTableCampo);
            tmp.str("");

            tmp<<campos.at(i)->getDecimal();
            s=tmp.str();
            itemTableCampo= new QTableWidgetItem(0);
            itemTableCampo->setText(s.c_str());
            tableCampo->setItem(i,3,itemTableCampo);
            tmp.str("");

            int llave=campos.at(i)->getLlave();
            if(llave==1)
                tmp<<"Si";
            else
                tmp<<"No";
            s=tmp.str();
            itemTableCampo= new QTableWidgetItem(0);
            itemTableCampo->setText(s.c_str());
            tableCampo->setItem(i,4,itemTableCampo);
            tmp.str("");
        }
        dialoglistarCampo->show();
        tableCampo->show();
}

void MainWindow::click_aceptarCrearCampo(){
    Campo* c = new Campo();
    string nombre="";
    int tipo=0;
    int longitud=0;
    int decimal=0;
    bool llave = false;
    nombre=lineNombreCampo->text().toStdString();
    tipo=comboTipoCampo->currentIndex();
    longitud=spinLongitud->text().toInt();
    decimal=spinDecimal->text().toInt();
    llave=checkLlave->isChecked();
    if(nombre.length ()==0 ||longitud<=decimal){
        errorM=new QErrorMessage(this);
        errorM->showMessage("Hubo un error al querer crear el campo");
    }
    else{
        c->crearCampo(nombre,tipo,longitud,decimal,llave);
        campos.push_back(c);
        lineNombreCampo->setText("");
        comboTipoCampo->setCurrentIndex(0);
        spinLongitud->setValue(1);
        spinDecimal->setValue(0);
        checkLlave->setChecked(false);
    }
}

void MainWindow::click_cancelarCampo(){
    dialogcrearCampo->close();
}

void MainWindow::click_aceptarListarCampo(){
    dialoglistarCampo->close();
}

void MainWindow::cambiarTipoCampo(){
    int tmp=comboTipoCampo->currentIndex();
    if(tmp==2){
        spinDecimal->setEnabled(true);
    }
    else{
        spinDecimal->setEnabled(false);
    }
}

//Funciones Menu Registro
void MainWindow::introducirRegistro(){
    if(campos.size()==0 || !archivo->isOpen()){
        errorM=new QErrorMessage(this);
        errorM->showMessage("Primero Introduzca Campos y Guarde el archivo");
    }
    else{
        registro.clear();
        stringstream tmp;
        for (unsigned int i = 0; i < campos.size(); i++) {
            int tipo = campos.at(i)->getTipo();
            if(tipo==0){
                QString cadena=QInputDialog::getText(this,QString(campos.at(i)->getNombre().c_str()),QString(campos.at(i)->getNombre().c_str()),QLineEdit::Normal,"");
                registro.push_back(cadena.toStdString());
            }
            if(tipo==1){
                int entero=QInputDialog::getInt(this,QString(campos.at(i)->getNombre().c_str()),QString(campos.at(i)->getNombre().c_str()));
                tmp<<entero;
                registro.push_back(tmp.str());
                tmp.str("");
            }
            if(tipo==2){
                double max=pow(10,campos.at(i)->getLongitud()-campos.at(i)->getDecimal());
                double real=QInputDialog::getDouble(this,QString(campos.at(i)->getNombre().c_str()),QString(campos.at(i)->getNombre().c_str()),0,-10000,max,campos.at(i)->getDecimal());
                tmp<<real;
                registro.push_back(tmp.str());
                tmp.str("");
            }
        }
        Registro* r= new Registro();
        r->crearRegistro(registro,campos);
        if(!archivo->addRecord(r,indices)){
            errorM=new QErrorMessage(this);
            errorM->showMessage("El registro con esa llave ya existe");
        }
        else{
            regIntroducido=true;
        }
    }
}

void MainWindow::crearDialogoIntroducirRegistro(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}

void MainWindow::buscarRegistro(){
    QString cadena=QInputDialog::getText(this,"Llave","Llave",QLineEdit::Normal,"");
    Registro* r=archivo->searchRecord(cadena.toStdString(),campos,indices);
    if(r==NULL){
        errorM=new QErrorMessage(this);
        errorM->showMessage("No existe ese registro");
    }
    else{
        registro=r->getRegistro();

        //Dialogo Buscar Registo
        dialogBuscarRegistro=new QDialog(this);
        dialogBuscarRegistro->hide();
        dialogBuscarRegistro->setWindowModality(Qt::WindowModal);
        dialogBuscarRegistro->setWindowTitle("Registro");
        dialogBuscarRegistro->setMinimumWidth(300);

        aceptarBuscarRegistro= new QPushButton("Aceptar",dialogBuscarRegistro);
        connect(aceptarBuscarRegistro,SIGNAL(clicked()),this, SLOT(click_aceptaBuscarRegistro()));

        QLabel* l;
        QLineEdit* le;
        int x1=40,x2=100,y=50;
        for(unsigned int i=0; i<campos.size(); i++){
            l=new QLabel(QString(campos.at(i)->getNombre().c_str()),dialogBuscarRegistro);
            l->move(x1,y);
            le=new QLineEdit(QString(registro.at(i).c_str()),dialogBuscarRegistro);
            le->setReadOnly(true);
            le->move(x2,y);
            y+=50;
        }
        dialogBuscarRegistro->setMinimumHeight(y+100);
        aceptarBuscarRegistro->move(100,y);
        dialogBuscarRegistro->show();
    }

}

 void MainWindow::click_aceptaBuscarRegistro(){
     dialogBuscarRegistro->close();
 }

void MainWindow::borrarRegistro(){
    QString cadena=QInputDialog::getText(this,"Llave","Llave",QLineEdit::Normal,"");
    if(!archivo->deleteRecord(cadena.toStdString(),indices)){
        errorM=new QErrorMessage(this);
        errorM->showMessage("El registro no existe");
    }
}

void MainWindow::listarRegistro(){
    tableRegistro=new QTableWidget(this);
    tableRegistro->move(50,50);
    tableRegistro->setMinimumSize(600,220);
    QStringList titulo;
    for(unsigned int i=0; i<campos.size();i++){
        titulo<<campos.at(i)->getNombre().c_str();
    }
    tableRegistro->setColumnCount(campos.size());
    tableRegistro->setHorizontalHeaderLabels(titulo);
    tableRegistro->resizeColumnsToContents();
    registros=archivo->listRecord(campos,indices);
    tableRegistro->setRowCount(registros.size());
    Registro* r;
    for(unsigned int i=0;i<registros.size();i++){
        r=registros.at(i);
        registro=r->getRegistro();
        for(unsigned int j=0;j<registro.size();j++){
            itemTableRegistro= new QTableWidgetItem(0);
            itemTableRegistro->setText(registro.at(j).c_str());
            tableRegistro->setItem(i,j,itemTableRegistro);
        }
    }
    tableRegistro->show();
}

//Funciones Menu Indices
void MainWindow::crearIndiceSimple(){
    if(!archivo->isOpen() || !regIntroducido){
        errorM=new QErrorMessage(this);
        errorM->showMessage("Primero tiene que guardar el archivo e Ingresar Registros");
    }
    else{
        archivo->guardarIndices(indices,fn);
    }
}

void MainWindow::crearArbolB(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}

void MainWindow::reindexar(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}

void MainWindow::importarXML(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}

void MainWindow::exportarXML(){
    archivo->guardarXML(campos,indices,fn);

}

void MainWindow::importarJSON(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}

void MainWindow::exportarJSON(){
    errorM=new QErrorMessage(this);
    errorM->showMessage("Oh-no! Lucia no hizo esta parte");
}


//----------------------------
void MainWindow::activardesactivarMenus(bool opcion){
    actionNuevoArchivo->setEnabled(!opcion);
    actionAbrirArchivo->setEnabled(!opcion);
    actionGuardarArchivo->setEnabled(opcion);
    actionCerrarArchivo->setEnabled(opcion);
    actionImprimirArchivo->setEnabled(opcion);
    actionCrearCampo->setEnabled(opcion);
    actionListarCampo->setEnabled(opcion);
    actionIntroducirRegistro->setEnabled(opcion);
    actionBuscarRegistro->setEnabled(opcion);
    actionBorrarRegistro->setEnabled(opcion);
    actionListarRegistro->setEnabled(opcion);
    actionCrearIndiceSimple->setEnabled(opcion);
    actionCrearArbolB->setEnabled(opcion);
    actionReindexar->setEnabled(opcion);
    actionImportarXML->setEnabled(opcion);
    actionExportarXML->setEnabled(opcion);
    actionImportarJSON->setEnabled(opcion);
    actionExportarJSON->setEnabled(opcion);

}



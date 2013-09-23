#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QErrorMessage>
#include <QInputDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QStringList>
#include <QLabel>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

/*#include <QListWidget>
#include <QListWidgetItem>*/

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <map>
#include <vector>
#include <math.h>

#include "Campo.h"
#include "Header.h"
#include "TDARecordFile.h"
#include "Index.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QErrorMessage* errorM;

    //Menu Archivo
    QMenu* mArchivo;
    QAction* actionNuevoArchivo;
    QAction* actionAbrirArchivo;
    QAction* actionGuardarArchivo;
    QAction* actionImprimirArchivo;
    QAction* actionCerrarArchivo;
    QAction* actionSalirArchivo;

    //Menu Campos
    QMenu* mCampo;
    QAction* actionCrearCampo;
    QAction* actionListarCampo;

    //Menu Registro
    QMenu* mRegistro;
    QAction* actionIntroducirRegistro;
    QAction* actionBuscarRegistro;
    QAction* actionBorrarRegistro;
    QAction* actionListarRegistro;

    //Menu Indices
    QMenu* mIndices;
    QAction* actionCrearIndiceSimple;
    QAction* actionCrearArbolB;
    QAction* actionReindexar;

    //Menu Utilidades
    QMenu* mUtilidades;
    QAction* actionImportarXML;
    QAction* actionExportarXML;
    QAction* actionImportarJSON;
    QAction* actionExportarJSON;


    //Dialogo crear Campo
    QDialog* dialogcrearCampo;
    QPushButton* aceptarcrearCampo;
    QPushButton* cancelarcrearCampo;
    QLineEdit* lineNombreCampo;
    QComboBox* comboTipoCampo;
    QSpinBox* spinLongitud;
    QSpinBox* spinDecimal;
    QCheckBox* checkLlave;
    QLabel* labelCampo;

    //Dialogo listar Campos
    QDialog* dialoglistarCampo;
    QTableWidget* tableCampo;
    QTableWidgetItem* itemTableCampo;
    QPushButton* aceptarlistarCampo;

    //Dialogo Buscar Registro
    QDialog* dialogBuscarRegistro;
    QPushButton* aceptarBuscarRegistro;

    //Mostrar Registros
    QTableWidget* tableRegistro;
    QTableWidgetItem* itemTableRegistro;
    QPushButton* aceptarlistarRegistro;

    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    //Slots Menu Archivo
    void nuevoArchivo();
    void abrirArchivo();
    void guardarArchivo();
    void imprimirArchivo();
    void cerrarArchivo();
    void salir();

    //Slots Menu Campos
    void crearCampo();
    void listarCampo();

    //Slots Menu Registro
    void introducirRegistro();
    void buscarRegistro();
    void borrarRegistro();
    void listarRegistro();

    //Slots Menu Indices
    void crearIndiceSimple();
    void crearArbolB();
    void reindexar();

    //Slots Menu Utilidades
    void importarXML();
    void exportarXML();
    void importarJSON();
    void exportarJSON();

    //Slots QDialog Crear Campo
    void cambiarTipoCampo();
    void click_aceptarCrearCampo();
    void click_cancelarCampo();

    //Slots QDialog Listar Campo
    void click_aceptarListarCampo();

    //Slots QDialog Buscar Registro
    void click_aceptaBuscarRegistro();


private:
    void crearActions();
    void agregar();
    void activardesactivarMenus(bool);
    void crearDialogoIntroducirRegistro();

    TDARecordFile* archivo;
    Header* header;
    Index* indices;
    vector<Campo*> campos;
    vector<string> registro;
    vector<Registro*> registros;
    bool regIntroducido;
    string fn;

};
#endif // MAINWINDOW_H

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new QWidget);
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");


}

MainWindow::~MainWindow()
{
}



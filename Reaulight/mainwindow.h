#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "sauvegarder_ou_importer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;


    sauvegarder_ou_importer SoI;

};
#endif // MAINWINDOW_H

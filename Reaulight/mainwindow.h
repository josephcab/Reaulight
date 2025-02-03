#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QDir>
#include <QDesktopServices>
#include <QList>
#include <QTabWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QLabel>
#include "projecteur.h"
#include "sauvegarder_ou_importer.h"
#include "arborescence_projet.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    QString ouvrirDialogue();

private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QMenu *menuAide;

    Projecteur *proj1;
    sauvegarder_ou_importer SoI;

    QFileSystemModel *modelExplorer; // Modèle pour l'onglet "Explorateur"
    arborescence_projet *arborescence;
    QTabWidget *tabWidget; // Onglets
    QDockWidget *dockGauche; // Panneau latéral
};
#endif // MAINWINDOW_H

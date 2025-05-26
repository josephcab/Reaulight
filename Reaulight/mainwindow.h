#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QDir>
#include <QDesktopServices>
#include <QTabWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QLabel>
#include "items/projector.h"
#include "sauvegarder_ou_importer.h"
#include "arborescence_projet.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QMenu *menuAide;

    Projector *proj1;
    Save_or_import* SoI;

    QFileSystemModel *modelExplorer; // Modèle pour l'onglet "Explorateur"
    arborescence_projet *arborescence;
    QTabWidget *tabWidget; // Onglets
    QDockWidget *dockGauche; // Panneau latéral
    QDockWidget *dockBas; // Panneau complémentaire
};
#endif // MAINWINDOW_H

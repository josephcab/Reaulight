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
#include "projecteur.h"
#include "sauvegarder_ou_importer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ouvrirDialogue();

private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;

    Projecteur *proj1;
    sauvegarder_ou_importer SoI;

    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QTreeView *treeView;
    QFileSystemModel *model;    
    QTabWidget *tabWidget;
    QDockWidget *dock;
};
#endif // MAINWINDOW_H

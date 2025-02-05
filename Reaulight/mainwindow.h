#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QList>
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
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QList>
<<<<<<< Updated upstream
#include "projecteur.h"
=======
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
    Projecteur *proj1;
=======
>>>>>>> Stashed changes
    sauvegarder_ou_importer SoI;

    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
};
#endif // MAINWINDOW_H

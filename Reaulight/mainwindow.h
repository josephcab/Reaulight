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
#include <QDebug>

#include "projecteur.h"
#include "sauvegarder_ou_importer.h"
#include "arborescence_projet.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /// @brief Accesseur de la liste des instances de projecteur
    /// @return liste de projecteur instancié
    QList<Projecteur*> get_instanced_projector();

    /// @brief Méthode permettant d'instancier un projecteur dans la scène
    /// @param pos, poisiton du projecteur dans la scène 3d -> QVector3D
    /// @param address adresse à modifier -> type int
    /// @param distance_attache_rotation distance entre le point d'attache du projecteur et son centre de rotation -> type double
    /// @param angle, angle d'éclairage du projecteur courant -> type double
    void instance_projector(QVector3D pos, int adress, double distance_attache_rotation, double angle);

    /// @brief Méthode permettant de désinstancier un projecteur en y accédant via son index
    /// @param index, index du projecteur à désintancier -> type int
    void uninstance_projector(int index);

public slots:


private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QMenu *menuAide;

    Projecteur *proj1;
    QList<Projecteur*> projecteur; // Liste des projecteurs instanciés
    sauvegarder_ou_importer SoI;

    QFileSystemModel *modelExplorer; // Modèle pour l'onglet "Explorateur"
    arborescence_projet *arborescence;
    QTabWidget *tabWidget; // Onglets
    QDockWidget *dockGauche; // Panneau latéral
    QDockWidget *dockBas; // Panneau complémentaire
};
#endif // MAINWINDOW_H

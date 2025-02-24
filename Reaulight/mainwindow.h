#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QList>
#include <QDebug>
#include "projector.h"
#include "sauvegarder_ou_importer.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /// @brief Accesseur de la liste des instances de projecteur
    /// @param index, index de la liste auquel accéder -> type int
    /// @return projecteur associé à l'index en paramètre, renvoie un pointeur nulle si index out of range -> type Projecteur
    Projector* get_instanced_projector(int index);

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
    void ouvrirDialogue();

private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QList<Projector*> projector; // liste d'instance des projecteurs utilisés dans le projet
    sauvegarder_ou_importer SoI;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
};
#endif // MAINWINDOW_H

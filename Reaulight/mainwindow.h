#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <vector>
#include "projecteur.h"
#include <iostream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /// @brief Accesseur de la liste des instances de projecteur
    /// @return liste de projecteur instancié
    std::vector<Projecteur*> get_instanced_projecteur();

    /// @brief Méthode permettant d'instancier un projecteur dans la scène
    /// @param pos, poisiton du projecteur dans la scène 3d -> QVector3D
    /// @param address adresse à modifier -> type int
    /// @param distance_attache_rotation distance entre le point d'attache du projecteur et son centre de rotation -> type double
    /// @param angle, angle d'éclairage du projecteur courant -> type double
    void instance_projecteur(QVector3D pos, int adress, double distance_attache_rotation, double angle);

    /// @brief Méthode permettant de désinstancier un projecteur en y accédant via son index
    /// @param index, index du projecteur à désintancier -> type int
    void uninstance_projecteur(int index);

private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    std::vector<Projecteur*> projecteur; // liste d'instance des projecteurs utilisés dans le projet
};
#endif // MAINWINDOW_H

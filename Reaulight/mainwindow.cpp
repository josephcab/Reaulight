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

QList<Projecteur*> MainWindow::get_instanced_projector()
{
    return this->projecteur;
}

void MainWindow::instance_projector(QVector3D pos, int adress, double distance_attache_rotation, double angle)
{
    this->projecteur.append(new Projecteur(pos, adress, distance_attache_rotation, angle));
}

void MainWindow::uninstance_projector(int index)
{
    // on regarde si on a un index out of range
    if ((int)(this->projecteur.size()) > index && index >= 0)
    {
        delete this->projecteur[index]; // désintancie le projecteur
        this->projecteur.erase(this->projecteur.begin() + index); // supprime un élément à un index
    }
    else // si oui, on lève une erreur
    {
        std::cerr << "List index out of range, vous ne pouvez pas supprimer un projecteur à un emplacement mémoire indéfinie" << std::endl;
    }
}

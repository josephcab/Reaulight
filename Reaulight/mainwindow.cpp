#include "mainwindow.h"
#include "OpenGL/openglwidget.h"

void MainWindow::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné: \n" + fichier); //Ouvre une fenêtre d'information concernant le fichier sélectionné
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->window()->setGeometry(0,0,1000,600); //ouvre le logiciel avec une taille de 1000x600
    setCentralWidget(new QWidget);
    menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionOuvrir = new QAction("&Ouvrir", this);
    menuFichier->addAction(actionOuvrir);
    connect(actionOuvrir, &QAction::triggered, this, &MainWindow::ouvrirDialogue);
    QMenu *fichiersRecents = menuFichier->addMenu("&Fichiers récents");
    fichiersRecents->addAction("Fichier bidon 1.txt");
    fichiersRecents->addAction("Fichier bidon 2.txt");
    fichiersRecents->addAction("Fichier bidon 3.txt");
    QAction *actionEnregistrer = new QAction("&Enregistrer", this);
    menuFichier->addAction(actionEnregistrer);
    QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
    menuFichier->addAction(actionEnregistrerSous);
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    menuEdition = menuBar()->addMenu("&Edition");

    menuAffichage = menuBar()->addMenu("&Affichage");


    QDockWidget *dockWidget = new QDockWidget(tr("Menu de gauche"), this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidgetContents = new QWidget();
    dockWidget->setWidget(dockWidgetContents);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    dockWidget->setFeatures(dockWidget->features() & QDockWidget::NoDockWidgetFeatures);
    dockWidget->setFeatures(dockWidget->features() & QDockWidget::DockWidgetVerticalTitleBar);
    dockWidget->setMinimumSize(200, 200);

    SoI.init();
    SoI.dialog(save);

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
        qDebug() << "List index out of range, vous ne pouvez pas supprimer un projecteur à un emplacement mémoire indéfinie";
    }
}

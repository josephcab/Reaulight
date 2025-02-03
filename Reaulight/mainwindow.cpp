#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->window()->setGeometry(0,0,1000,600);
    SoI.init(); // initialisation de SoI
    setCentralWidget(new QWidget);
    menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionOuvrir = new QAction("&Ouvrir", this);
    menuFichier->addAction(actionOuvrir);
    connect(actionOuvrir, &QAction::triggered, this, [this](){
        SoI.dialog(import);
    });
    QMenu *fichiersRecents = menuFichier->addMenu("&Fichiers récents");
    QAction *actionEnregistrer = new QAction("&Enregistrer", this);
<<<<<<< Updated upstream
=======
    connect(actionEnregistrer, &QAction::triggered, this, [this](){
        SoI.dialog(saveIfOpen);
    });
>>>>>>> Stashed changes
    menuFichier->addAction(actionEnregistrer);
    QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
    menuFichier->addAction(actionEnregistrerSous);
    connect(actionEnregistrerSous, &QAction::triggered, this, [this](){
        SoI.dialog(save);
    });
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

}

MainWindow::~MainWindow()
{
}

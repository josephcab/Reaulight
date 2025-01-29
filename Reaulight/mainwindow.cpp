#include "mainwindow.h"

void MainWindow::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné: \n" + fichier); //Ouvre une fenêtre d'information concernant le fichier sélectionné
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    SoI.init();
    this->window()->setGeometry(0,0,1000,600); //ouvre le logiciel avec une taille de 1000x600
    setCentralWidget(new QWidget);
    menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionOuvrir = new QAction("&Ouvrir", this);
        menuFichier->addAction(actionOuvrir);
        connect(actionOuvrir, &QAction::triggered, this, &MainWindow::ouvrirDialogue);
    QAction *actionImporter = new QAction("&Importer", this);
        menuFichier->addAction(actionImporter);
        connect(actionImporter, &QAction::triggered, this, [this]() {SoI.dialog(dialogType::import);});
    QMenu *fichiersRecents = menuFichier->addMenu("&Fichiers récents");
        fichiersRecents->addAction("Fichier bidon 1.txt");
        fichiersRecents->addAction("Fichier bidon 2.txt");
        fichiersRecents->addAction("Fichier bidon 3.txt");
    QAction *actionSauvegarder = new QAction("&Sauvegarder", this);
        menuFichier->addAction(actionSauvegarder);
        connect(actionSauvegarder, &QAction::triggered, this, [this]() {SoI.dialog(dialogType::save);});
    QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
        menuFichier->addAction(actionEnregistrerSous);
    QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, &QAction::triggered, qApp, &QApplication::quit);

    menuEdition = menuBar()->addMenu("&Edition");

    menuAffichage = menuBar()->addMenu("&Affichage");

    QDockWidget *dockWidget = new QDockWidget(tr("Explorateur de fichiers"), this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidgetContents = new QWidget();
    dockWidget->setWidget(dockWidgetContents);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    dockWidget->setFeatures(dockWidget->features() & QDockWidget::NoDockWidgetFeatures);
    dockWidget->setFeatures(dockWidget->features() & QDockWidget::DockWidgetVerticalTitleBar);
    dockWidget->setMinimumSize(500, 250); // largeur, hauteur

    model = new QFileSystemModel(this); // Créer le modèle pour afficher les fichiers
    model->setRootPath(QDir::homePath()); // Définir la racine (par défaut le dossier personnel)
    model->setNameFilters(QStringList() << "*.txt"); // Filtrer uniquement les fichiers .txt
    // Créer la vue arborescente (TreeView)
    treeView = new QTreeView();
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::homePath())); // Point d'entrée dans l'arborescence
    dockWidget->setWidget(treeView); //Ajoute la vue explorer au dock de gauche
}

MainWindow::~MainWindow() {}

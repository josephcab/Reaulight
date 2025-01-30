#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>

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

    tabWidget = new QTabWidget(); // Créer le QTabWidget

    // Onglet 1'Explorateur
    QWidget *tabExplorer = new QWidget();
    QVBoxLayout *explorerLayout = new QVBoxLayout();
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath()); // Définir la racine (par défaut le dossier personnel)
    model->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    model->setNameFilters(QStringList() << "*.txt"); // Filtrer uniquement les fichiers .txt
    // Gère la partie inclusion de l'explorateur
    treeView = new QTreeView();
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::homePath()));
    // Gère la partie affichage de l'explorateur
    explorerLayout->addWidget(treeView);
    tabExplorer->setLayout(explorerLayout);
    tabWidget->addTab(tabExplorer, "Explorateur");

    // Onglet 2 (exemple)
    QWidget *tab1 = new QWidget();
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(new QLabel("Contenu de l'onglet 1"));
    tab1->setLayout(layout1);
    tabWidget->addTab(tab1, "Onglet 1");

    // Ajouter le QTabWidget dans un QDockWidget
    dock = new QDockWidget("Panneau latéral", this);
    dock->setWidget(tabWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->setMinimumWidth(450);
    dock->setMaximumWidth(500);
    dock->setFeatures(dock->features() & QDockWidget::NoDockWidgetFeatures);
    dock->setFeatures(dock->features() & QDockWidget::DockWidgetVerticalTitleBar);
}

MainWindow::~MainWindow() {}

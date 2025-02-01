#include "mainwindow.h"

QString MainWindow::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné : \n" + fichier); //Ouvre une fenêtre d'information concernant le fichier sélectionné
    return fichier;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    modelExplorer(nullptr),
    modelArborescence(nullptr),
    tabWidget(nullptr),
    dockGauche(nullptr)
{
    SoI.init();
    this->window()->setGeometry(0, 0, 1000, 600); // Taille de la fenêtre (L=1'000 ; l=600) à la position X=0 ; Y=0
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

    menuAffichage = menuBar()->addMenu("&Affichage 3D");

    menuAide = menuBar()->addMenu("&Aide");
        QAction *actionDépôtGithub = new QAction("&Dépôt Github", this);
            menuAide->addAction(actionDépôtGithub);
        QAction *actionDiscussionGithub = new QAction("&Salon de discussion Github", this);
            menuAide->addAction(actionDiscussionGithub);
        QAction *actionDiscord = new QAction("&Serveur Discord", this);
            menuAide->addAction(actionDiscord);
        QAction *actionQt = new QAction("&À propos de Qt", this);
            menuAide->addAction(actionQt);
        QAction *actionRéaulight = new QAction("&À propos de Réaulight", this);
            menuAide->addAction(actionRéaulight);

    // Initialisation des modèles
        modelArborescence = new QStandardItemModel(this);
        modelExplorer = new QFileSystemModel(this);
        modelExplorer->setRootPath(QDir::homePath());
        modelExplorer->setFilter(QDir::Files | QDir::NoDotAndDotDot);
        modelExplorer->setNameFilters(QStringList() << "*.txt");

    // Création des vues
        QTreeView *treeExplorer = new QTreeView();
        treeExplorer->setModel(modelExplorer);
        treeExplorer->setRootIndex(modelExplorer->index(QDir::homePath()));

        QTreeView *treeArborescence = new QTreeView();
        treeArborescence->setModel(modelArborescence);
        treeArborescence->expandAll();

    // Création des onglets
        tabWidget = new QTabWidget(this);
        tabWidget->addTab(treeExplorer, "Explorateur");
        tabWidget->addTab(treeArborescence, "Arborescence");

    // Ajouter les onglets dans un QDockWidget
        dockGauche = new QDockWidget("Panneau latéral", this);
        dockGauche->setWidget(tabWidget);
        addDockWidget(Qt::LeftDockWidgetArea, dockGauche);
        dockGauche->setMinimumWidth(425);
        dockGauche->setMaximumWidth(425);
        dockGauche->setFeatures(dockGauche->features() & QDockWidget::NoDockWidgetFeatures);
        dockGauche->setFeatures(dockGauche->features() & QDockWidget::DockWidgetVerticalTitleBar);
}

MainWindow::~MainWindow() {}

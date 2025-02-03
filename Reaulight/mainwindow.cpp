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
    arborescence(new arborescence_projet(this)), // Initialisation de la classe arborescence_projet
    tabWidget(nullptr),
    dockGauche(nullptr)
{
    SoI.init();
    this->window()->setGeometry(0, 0, 1000, 600); // Taille de la fenêtre (L=1'000 ; l=600) à la position X=0 ; Y=0
    setCentralWidget(new QWidget);

    menuFichier = menuBar()->addMenu("&Fichier");
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
        QAction *actionUpdate = new QAction("&Chercher des mises à jour", this);
            menuAide->addAction(actionUpdate);
            connect(actionUpdate, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/releases"));});
        QAction *actionDépôtGithub = new QAction("&Dépôt Github", this);
            menuAide->addAction(actionDépôtGithub);
            connect(actionDépôtGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight"));});
        QAction *actionDiscussionGithub = new QAction("&Salon de discussion Github", this);
            menuAide->addAction(actionDiscussionGithub);
            connect(actionDiscussionGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/discussions/10"));});
        QAction *actionDiscord = new QAction("&Serveur Discord", this);
            menuAide->addAction(actionDiscord);
            connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/WmrxwnUY89"));});
        QAction *actionQt = new QAction("&À propos de Qt", this);
            menuAide->addAction(actionQt);
            connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
        QAction *actionRéaulight = new QAction("&À propos de Réaulight", this);
            menuAide->addAction(actionRéaulight);
            connect(actionRéaulight, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/blob/main/README.md"));});

    // Initialisation des modèles
        modelExplorer = new QFileSystemModel(this);
        modelExplorer->setRootPath(QDir::homePath());
        modelExplorer->setFilter(QDir::Files | QDir::NoDotAndDotDot);
        modelExplorer->setNameFilters(QStringList() << "*.txt");

    // Création des vues
        QTreeView *treeExplorer = new QTreeView();
            treeExplorer->setModel(modelExplorer);
            treeExplorer->setRootIndex(modelExplorer->index(QDir::homePath()));
        QTreeView *treeArborescence = new QTreeView();
            treeArborescence->setModel(arborescence->getModel()); // Utilisation du modèle de arborescence_projet

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

    // Exemple d'ajout d'éléments à l'arborescence
        arborescence->addSpectacle("Spectacle 1");
        QStandardItem *spectacle1 = arborescence->getModel()->item(0); // Récupère le premier spectacle
            arborescence->addUnivers(spectacle1, "Univers 1");
            arborescence->addReseau(spectacle1, "Réseau 1");
            QStandardItem *univers1 = spectacle1->child(0); // Récupère le premier univers<
                arborescence->addMaterielDMX(univers1, "Matériel DMX 1");
        treeArborescence->expandAll();
}

MainWindow::~MainWindow() {}

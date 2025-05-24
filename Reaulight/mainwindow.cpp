#include "mainwindow.h"
#include "OpenGL/openglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    modelExplorer(nullptr),
    arborescence(new arborescence_projet(this)), // Initialisation de la classe arborescence_projet
    tabWidget(nullptr),
    dockGauche(nullptr)
{
    SoI = new Save_or_import();
    SoI->init(window());
    this->window()->setGeometry(0, 0, 1000, 600); // Taille de la fenêtre (L=1'000 ; l=600) à la position X=0 ; Y=0
    setCentralWidget(new QWidget);

    menuFichier = menuBar()->addMenu("&Fichier");
        QAction *actionImporter = new QAction("&Importer", this);
            menuFichier->addAction(actionImporter);
            connect(actionImporter, &QAction::triggered, this, [this]() {SoI->dialog(dialogType::import);});
        QMenu *fichiersRecents = menuFichier->addMenu("&Fichiers récents");
            fichiersRecents->addAction("Fichier bidon 1.txt");
            fichiersRecents->addAction("Fichier bidon 2.txt");
            fichiersRecents->addAction("Fichier bidon 3.txt");
        QAction *actionSauvegarder = new QAction("&Sauvegarder", this);
            menuFichier->addAction(actionSauvegarder);
            connect(actionSauvegarder, &QAction::triggered, this, [this]() {SoI->dialog(dialogType::saveIfOpen);});
        QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
            menuFichier->addAction(actionEnregistrerSous);
            connect(actionEnregistrerSous, &QAction::triggered, this, [this]() {SoI->dialog(dialogType::save);});
    menuFichier->addSeparator();
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
            connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/H7wEZ8mUKc"));});
    menuAide->addSeparator();
        QAction *actionQt = new QAction("&À propos de Qt", this);
            menuAide->addAction(actionQt);
            connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
        QAction *actionRéaulight = new QAction("&À propos de Réaulight", this);
            menuAide->addAction(actionRéaulight);
            connect(actionRéaulight, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/blob/main/README.md"));});

    QAction *toggleTheme = new QAction("&Changer de thème", this);
    menuBar()->addAction(toggleTheme);

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
        tabWidget->setCurrentIndex(tabWidget->indexOf(treeArborescence));

    // Ajouter les onglets dans un QDockWidget
        dockGauche = new QDockWidget("Panneau latéral", this);
        dockGauche->setWidget(tabWidget);
        addDockWidget(Qt::LeftDockWidgetArea, dockGauche);
        dockGauche->setMinimumSize(200, 400);
        dockGauche->setMaximumSize(300, 500);
        dockGauche->setFeatures(dockGauche->features() & QDockWidget::NoDockWidgetFeatures);

    // Exemple d'ajout d'éléments à l'arborescence
        arborescence->addSpectacle("Spectacle 1");
        QStandardItem *spectacle1 = arborescence->getModel()->item(0); // Récupère le premier spectacle
            arborescence->addUnivers(spectacle1, "Univers 1");
            arborescence->addReseau(spectacle1, "Réseau 1");
            QStandardItem *univers1 = spectacle1->child(0); // Récupère le premier univers<
                arborescence->addMaterielDMX(univers1, "Matériel DMX 1");
        treeArborescence->expandAll();

    //recup les données pour l'enregristrer du fichier .json
    connect(SoI, &Save_or_import::isSavingAccept, this, [this](bool accepted)
    {
        if(accepted == true)
        {
            /** A corriger **/
            //SoI->setProjectorList(this->projector); //envoyer tout les projecteurs pour la sauvegarde
        }
    });

    // Création d'un QDockWidget bas
    dockBas = new QDockWidget("Panneau complémentaire", this);
    addDockWidget(Qt::BottomDockWidgetArea, dockBas);
    dockBas->setMinimumWidth(300);
    dockBas->setMaximumWidth(600);
    dockBas->setFeatures(dockBas->features() & QDockWidget::NoDockWidgetFeatures);

    // Création du widget conteneur pour la grille
    QWidget *grille = new QWidget();  // La grille est déclarée comme un widget lambda
    dockBas->setWidget(grille);       // Assignation au dock

    // Création des boutons
    QLabel *statutType     = new QLabel("Type :", grille);
    QLabel *statutMarque   = new QLabel("Marque :", grille);
    QLabel *statutNom      = new QLabel("Nom :", grille);
    QLabel *statutModele   = new QLabel("Modèle :", grille);
    QComboBox *comboType   = new QComboBox(grille);
    QComboBox *comboMarque = new QComboBox(grille);
    QComboBox *comboNom    = new QComboBox(grille);
    QComboBox *comboModele = new QComboBox(grille);

    QSlider *frequence = new QSlider(Qt::Horizontal, grille);
        frequence->setRange(-100, 100);
        frequence->setSingleStep(1);
    QSlider *angle = new QSlider(Qt::Horizontal, grille);
        angle->setRange(-100, 100);
        angle->setSingleStep(1);
    //Qcolor

    // Création du layout en grille et y ajoute les boutons
    QGridLayout *layout = new QGridLayout(grille);  // Maintenant la grille est déclarée comme QGridLayout
    layout->addWidget(statutType,    0, 0);
    layout->addWidget(statutMarque,  1, 0);
    layout->addWidget(statutNom,     2, 0);
    layout->addWidget(statutModele,  3, 0);
    layout->addWidget(comboType,     0, 1);
    layout->addWidget(comboMarque,   1, 1);
    layout->addWidget(comboNom,      2, 1);
    layout->addWidget(comboModele,   3, 1);
    // Ajoute un séparateur vertical
    QFrame *separator = new QFrame();
        separator->setFrameShape(QFrame::VLine);
        separator->setFrameShadow(QFrame::Sunken);
        layout->addWidget(separator, 0, 2, 4, 1);
    layout->addWidget(frequence,     0, 3);
    layout->addWidget(angle,         0, 4);
}

MainWindow::~MainWindow() {}

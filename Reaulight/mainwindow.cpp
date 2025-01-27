#include "mainwindow.h"

void MainWindow::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné: \n" + fichier);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->window()->setGeometry(0,0,1000,600);
    setCentralWidget(new QWidget);
    menuFichier = menuBar()->addMenu("&Fichier");
        QAction *actionOuvrir = new QAction("&Ouvrir", this);
        menuFichier->addAction(actionOuvrir);
        QMenu *fichiersRecents = menuFichier->addMenu("Fichiers &récents");
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

    connect(actionOuvrir, &QAction::triggered, this, &MainWindow::ouvrirDialogue);
}

MainWindow::~MainWindow()
{
}

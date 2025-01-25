#include "mainwindow.h"
#include "OpenGL/openglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    OpenGlWidget *widget_opengl = new OpenGlWidget;
    setCentralWidget(widget_opengl);
    widget_opengl->drawShape(OpenGlWidget::Rect);
    menuFichier = menuBar()->addMenu("&Fichier");
        QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");

    SoI.init();

    SoI.dialog(import);
}

MainWindow::~MainWindow()
{
}



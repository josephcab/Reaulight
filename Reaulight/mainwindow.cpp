#include "mainwindow.h"
#include "OpenGL/openglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    OpenGlWidget *widget_opengl = new OpenGlWidget;
    setCentralWidget(widget_opengl);
    widget_opengl->drawShape(OpenGlWidget::Rect);
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");
}

MainWindow::~MainWindow()
{
}



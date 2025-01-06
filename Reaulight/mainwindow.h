#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;

};
#endif // MAINWINDOW_H

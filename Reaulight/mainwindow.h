#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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

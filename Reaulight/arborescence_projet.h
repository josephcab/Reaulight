#ifndef ARBORESCENCE_PROJET_H
#define ARBORESCENCE_PROJET_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>

class arborescence_projet : public QObject
{
    Q_OBJECT

public:
    arborescence_projet(QObject *parent = nullptr);
    ~arborescence_projet();

public slots:
    void addSpectacle(const QString &name);
    void addUnivers(QStandardItem *spectacleItem, const QString &name);
    void addReseau(QStandardItem *spectacleItem, const QString &name);
    void addMaterielDMX(QStandardItem *universItem, const QString &name);

    QStandardItemModel* getModel() const; // Getter pour le modèle

private:
    QStandardItemModel *model; // Modèle pour l'arborescence
};

#endif // ARBORESCENCE_PROJET_H

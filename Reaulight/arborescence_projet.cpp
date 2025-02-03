#include "arborescence_projet.h"

arborescence_projet::arborescence_projet(QObject *parent)
    : QObject(parent),
    model(new QStandardItemModel(this))
{
    // Initialisation du modèle
    model->setHorizontalHeaderLabels(QStringList() << "Nom");
}

void arborescence_projet::addSpectacle(const QString &name)
{
    QStandardItem *spectacleItem = new QStandardItem("📁 " + name);
    model->appendRow(spectacleItem);
}

    void arborescence_projet::addUnivers(QStandardItem *spectacleItem, const QString &name)
    {
        QStandardItem *universItem = new QStandardItem("🌍 " + name);
        spectacleItem->appendRow(universItem);
    }

        void arborescence_projet::addMaterielDMX(QStandardItem *universItem, const QString &name)
        {
            QStandardItem *materielItem = new QStandardItem("🎛️ " + name);
            universItem->appendRow(materielItem);
        }

    void arborescence_projet::addReseau(QStandardItem *spectacleItem, const QString &name)
    {
        QStandardItem *reseauItem = new QStandardItem("🌐 " + name);
        spectacleItem->appendRow(reseauItem);
    }

QStandardItemModel* arborescence_projet::getModel() const
{
    return model;
}

arborescence_projet::~arborescence_projet() {}

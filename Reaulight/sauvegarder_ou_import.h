#ifndef SAUVEGARDER_OU_IMPORT_H
#define SAUVEGARDER_OU_IMPORT_H

//Sauvegarde des données de spectacle #5

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QStandardPaths>
#include <QString>
#include <QSysInfo>

enum dialogType {save, import};

class sauvegarder_ou_importer
{
public:
    sauvegarder_ou_importer();
    void init();
    void saveParty(); // sauvegarder tout dans un seul fichier.
    void importParty();
    void dialog(dialogType type);


private:
    QString defaultpath;
    QString pathChoose; // path choisi par l'utilisateur.

    QList<QJsonArray> proj_list; // list des projecteur
    QList<QJsonArray> staticObj_list; // list des obj static donc qui ne bouge pas
};

#endif // SAUVEGARDER_OU_IMPORT_H

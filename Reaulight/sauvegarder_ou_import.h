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
#include <QFileInfo>
#include <QStandardPaths>
#include <QString>
#include <QSysInfo>
#include <QMessageBox>
#include <QPushButton>

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
    QString import_file; // fichier importer
    QString defaultpath;
    QString pathChoose; // path choisi par l'utilisateur.
    QString roomName;
    QString date; // date de sauvegarde
    QString creator; //nom du créateur de la sallle
    QList<QJsonArray> room; // stocker les infos conscernant la salle
    QList<QJsonArray> projector; // liste des projecteur
};

#endif // SAUVEGARDER_OU_IMPORT_H

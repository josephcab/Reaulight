#ifndef SAUVEGARDER_OU_IMPORTER_H
#define SAUVEGARDER_OU_IMPORTER_H

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

enum dialogType {save, import, saveIfOpen};

class sauvegarder_ou_importer
{
public:
    sauvegarder_ou_importer();
    void init();
    void saveParty(); // sauvegarder tout dans un seul fichier.
    void savePartyWhenOpen();
    void importParty(QString path);
    void dialog(dialogType type);

private:
    QString defaultpath;
    QString pathChoose; // path choisi par l'utilisateur.
    QString roomName;
    QString date; // date de sauvegarde
    QString creator; //nom du créateur de la salle
    QList<QJsonArray> room; // stocker les infos concernant la salle
    QList<QJsonArray> projector; // liste des projecteurs
};

#endif // SAUVEGARDER_OU_IMPORTER_H

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
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>

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

    //geter
    //seter
    QString setRoomName(QString name);

private:
    QString defaultpath;
    QString pathChoose; // path choisi par l'utilisateur.

    QString roomName;
    QString saveDateTime;
    QString creator;
    QString fileSave;

    QJsonArray Scenes;
    QJsonArray Scenes_info; // exemple d'utilisation: Scenes.append(QJsonObject{{"Hauteur": "", "Largeur": "", "Position": {"x": "", "y": "", "z": ""}, "Oriantations" : {}, "id": ""}});
    QJsonArray Structures;
    QJsonArray Structures_info;
    QJsonArray Projecteurs;
    QJsonArray Projecteurs_info;
    QJsonArray Programme_du_show;
};

#endif // SAUVEGARDER_OU_IMPORTER_H

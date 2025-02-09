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
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QDate>

#include <projecteur.h>

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
    QList<Projecteur*> setProjecteurList(QList<Projecteur*> proj);

private:
    QString defaultpath;
    QString pathChoose; // path choisi par l'utilisateur.
    QDialog setOtherFileInfo; // boite de dialog pour choisir le nom du créateur
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


    QList<Projecteur*> proj_list; // list des projecteurs.

    bool savehasRun = false;


    //btn
    QPushButton* saveButton; // btn msgBox;
    QPushButton* cancelButton;
};

#endif // SAUVEGARDER_OU_IMPORTER_H

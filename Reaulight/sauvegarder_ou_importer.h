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

class Save_or_import : public QObject
{
    Q_OBJECT

public:
    explicit Save_or_import(QObject *parent = nullptr);
    void init();
    void saveParty(); // sauvegarder tout dans un seul fichier.
    void savePartyWhenOpen();
    void importParty(QString path);
    void dialog(dialogType type);

    //geter

    //seter
    QString setRoomName(QString name);
    void setProjectorList(QList<Projecteur*> proj);

signals:
    void isSavingAccept(bool accepted);
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
    QJsonArray Projector;
    QJsonArray Projector_info;
    QJsonArray Programme_du_show;

    bool savehasRun = false;


    //btn
    QPushButton* saveButton; // btn msgBox;
    QPushButton* cancelButton;
};


#endif // SAUVEGARDER_OU_IMPORTER_H

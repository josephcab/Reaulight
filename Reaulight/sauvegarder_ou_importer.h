#ifndef SAUVEGARDER_OU_IMPORTER_H
#define SAUVEGARDER_OU_IMPORTER_H

//Sauvegarde des données de spectacle #5

#include <QtWidgets>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "Items/projector.h"

enum dialogType {save, import, saveIfOpen};

class Save_or_import : public QObject
{
    Q_OBJECT

    public:
        explicit Save_or_import(QObject *parent = nullptr);
        void init(QWidget *window);
        void saveParty(); // sauvegarder tout dans un seul fichier.
        void savePartyWhenOpen();
        void importParty(QString path);
        void dialog(dialogType type);

        //geter

        //seter
        QString setRoomName(QString name);
        void setProjectorList(QList<Projector*> proj);

    signals:
        void isSavingAccept(bool accepted);

    private:
        QWidget *MainWindow; //variable pour le widget de la window principale

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
        QJsonArray Projectors;
        QJsonArray Projector_info;
        QJsonArray Programme_du_show;

        bool savehasRun = false;


        //dialog box for more information
        QPushButton* saveButton;
        QLineEdit* creatorNameInput;
        QLineEdit* roomNameInput;
};


#endif // SAUVEGARDER_OU_IMPORTER_H

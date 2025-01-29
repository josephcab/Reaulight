#include "sauvegarder_ou_importer.h"

sauvegarder_ou_importer::sauvegarder_ou_importer() {}

void sauvegarder_ou_importer::init()
{
    // Récupérer le chemin du dossier Documents de l'utilisateur.
    this->defaultpath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    this->defaultpath.append("/Documents");
}
void sauvegarder_ou_importer::saveParty()
{
    QString fileSave = this->pathChoose + "/test" + ".json";
    QJsonObject jsonObject;
    QString roomName = "";
    QString saveDateTime = "";
    QString creator = "";

    QJsonArray Scenes;
    QJsonArray Scenes_info; // exemple d'utilisation: Scenes.append(QJsonObject{{"Hauteur": "", "Largeur": "", "Position": {"x": "", "y": "", "z": ""}, "Oriantations" : {}, "id": ""}});
    QJsonArray Structures;
    QJsonArray Structures_info;
    QJsonArray Projecteurs;
    QJsonArray Projecteurs_info;
    QJsonArray Programme_du_show;


    if(!roomName.isEmpty() && !creator.isEmpty()) // si le nom de la salle n'est pas vide et que le nom du créateur n'est pas vide
    {
        jsonObject = QJsonObject{
            {"Nom_de_la_salle", roomName},
            {"Date_de_sauvegarde", saveDateTime},
            {"Createur", creator},
            {"Scenes", Scenes},
            {"Scenes_info", Scenes_info},
            {"Structures", Structures},
            {"Structures_info", Structures_info},
            {"Projecteurs", Projecteurs},
            {"Projecteurs_info", Projecteurs_info},
            {"Programme_du_showProgramme_du_show", Programme_du_show}
        };
    }
    QJsonDocument jdoc(jsonObject);
    QFile file(fileSave);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(jdoc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "fichier créer";
    }
    else
    {
        qDebug() << "Erreur";
    }
}
void sauvegarder_ou_importer::importParty(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray sBuf = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(sBuf);
    if (doc.isNull()) {
        qWarning() << "Le contenu du fichier n'est pas un JSON valide.";
        return;
    }
    QJsonObject Obj = doc.object();
    for(const QString &key : Obj.keys())
    {
        QJsonValue val = Obj.value(key);
        QJsonObject obj = val.toObject();
        QJsonArray arr = val.toArray();
        if(key == "Nom_de_la_salle")
        {
            qDebug() << key << ": " << val.toString();
        }
        else if(key == "Date_de_sauvegarde")
        {
            qDebug() << key << ": " << val.toString();
        }
        else if(key == "Createur")
        {
            qDebug() << key << ": " << val.toString();
        }
        else if(key == "Salle")
        {
            qDebug() << key << ": " << obj;
        }
        else if(key == "Scenes")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Scenes")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Scenes_info")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Structures")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Structures_info")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Projecteurs")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Projecteurs_info")
        {
            qDebug() << key << ": " << arr;
        }
        else if(key == "Programme_du_show")
        {
            qDebug() << key << ": " << arr;
        }
    }
}
void sauvegarder_ou_importer::dialog(dialogType type)
{

    if(type == import)
    {
        QString file = QFileDialog::getOpenFileName(nullptr, "Open File",this->pathChoose.isEmpty() ? this->defaultpath : this->pathChoose,"JSON Files (*.json);");
        this->importParty(file); // Lancer le code pour lire et importer toutes les données du fichier JSON
    }
    if(type == save)
    {
        QString folder_path = QFileDialog::getExistingDirectory(nullptr, "Select folder", this->defaultpath);

        if(!folder_path.isEmpty())
        {
            this->pathChoose = folder_path;
            //this->saveParty();  //Lancer la fonction pour enregistrer toutes les données.
        }
    }
}

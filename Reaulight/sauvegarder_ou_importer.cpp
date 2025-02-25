#include "sauvegarder_ou_importer.h"

Save_or_import::Save_or_import(QObject *parent)
    : QObject(parent), saveButton(nullptr), cancelButton(nullptr)
{
    saveButton = new QPushButton("Sauvegarder");
    cancelButton = new QPushButton("Annuler");
}

void Save_or_import::init()
{
    // Récupère directement le chemin du dossier Documents
    this->defaultpath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void Save_or_import::saveParty()
{
    setOtherFileInfo.resize(500, 200);
    setOtherFileInfo.setWindowTitle("Autres détails pour l'enregistrement");

    // Texte
    QLabel* text = new QLabel("Veuillez définir le nom du créateur !", &setOtherFileInfo);

    // Champ de texte
    QLineEdit* filenameInput = new QLineEdit(&setOtherFileInfo);
    filenameInput->setMinimumWidth(250);
    filenameInput->setMaximumHeight(40);
    filenameInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Boutons
    saveButton = new QPushButton("Sauvegarder", &setOtherFileInfo);
    cancelButton = new QPushButton("Annuler", &setOtherFileInfo);


    QObject::connect(cancelButton, &QPushButton::clicked, &setOtherFileInfo, &QDialog::reject);
    QObject::connect(saveButton, &QPushButton::clicked, &setOtherFileInfo, &QDialog::accept);

    // Mise en page
    QHBoxLayout* layout_horizontal = new QHBoxLayout();
    layout_horizontal->addWidget(saveButton);
    layout_horizontal->addWidget(cancelButton);

    QVBoxLayout* layout_vertical = new QVBoxLayout(&setOtherFileInfo);
    layout_vertical->addWidget(text);
    layout_vertical->addWidget(filenameInput);
    layout_vertical->addLayout(layout_horizontal);

    // Exécution de la boîte de dialogue
    int result = setOtherFileInfo.exec();
    if (result == QDialog::Accepted) {
        if (!filenameInput->text().isEmpty()) {
            this->creator = filenameInput->text();
        } else {
            QMessageBox::warning(&setOtherFileInfo, "Erreur", "Le nom du créateur ne peut pas être vide.");
            return;
        }
    } else {
        return; // Annuler la sauvegarde si l'utilisateur clique sur "Annuler"
    }

    emit isSavingAccept(true);
    QJsonObject jsonObject;
    roomName = this->roomName.isEmpty() ? "Room name has not been defined" : this->roomName;
    saveDateTime = QDate::currentDate().toString() + " at " + QTime::currentTime().toString(); // date de l'enregistrement
    fileSave = this->pathChoose + "/"+ roomName + ".json";

    if(!roomName.isEmpty() && !creator.isEmpty()) // si le nom de la salle n'est pas vide et que le nom du créateur n'est pas vide
    {
        jsonObject = QJsonObject{
            {"Nom_de_la_salle", this->roomName},
            {"Date_de_sauvegarde", this->saveDateTime},
            {"Createur", this->creator},
            {"Scenes", this->Scenes},
            {"Scenes_info", this->Scenes_info},
            {"Structures", this->Structures},
            {"Structures_info", this->Structures_info},
            {"Projecteurs", this->Projector},
            {"Projecteurs_info", this->Projector_info},
            {"Programme_du_show", this->Programme_du_show}
        };
    }
    else
    {
        return;
    }
    QJsonDocument jdoc(jsonObject);

    QFile file(fileSave);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(jdoc.toJson(QJsonDocument::Indented));
        file.close();
    } else {
        qDebug() << "Erreur lors de l'ouverture du fichier pour écriture :" << file.errorString();
    }
}

void Save_or_import::importParty(QString path)
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

void Save_or_import::savePartyWhenOpen()
{
    if (this->pathChoose.isEmpty()) // si l'utisilateur n'a pas enregistrer avant alors lui afficher cette msgbox
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Erreur");
        messageBox.setText("Vous n'avez pas enregistré votre scène.");
        messageBox.setIcon(QMessageBox::Warning);

        QPushButton* saveButton = messageBox.addButton("Enregistrer", QMessageBox::AcceptRole);
        QPushButton* cancelButton = messageBox.addButton("Ne pas enregistrer", QMessageBox::RejectRole);

        messageBox.exec();

        if (messageBox.clickedButton() == saveButton)
        {
            this->saveParty();
        }
    }
    //reste du code ici

    QFile file(this->pathChoose);
    file.open(QIODevice::ReadWrite);
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

}

void Save_or_import::dialog(dialogType type)
{
    if(type == import)
    {
        QString file = QFileDialog::getOpenFileName(nullptr, "Open File",this->pathChoose.isEmpty() ? this->defaultpath : this->pathChoose,"JSON Files (*.json);");
        if(!file.isEmpty())
        {
            this->importParty(file); // Lancer le code pour lire et importer toutes les données du fichier JSON
        }
    }
    if(type == save)
    {
        QString folder_path = QFileDialog::getExistingDirectory(nullptr, "Select folder", this->defaultpath);

        if(!folder_path.isEmpty())
        {
            this->pathChoose = folder_path;
            this->saveParty();  //Lancer la fonction pour enregistrer toutes les données.
        }
    }
    if(type == saveIfOpen)
    {
        this->savePartyWhenOpen();
    }
}


//seter
QString Save_or_import::setRoomName(QString name)
{
    return this->roomName = name;
}
void Save_or_import::setProjectorList(QList<Projecteur*> proj)
{
    QJsonArray convertQlistToArray;

    for (const auto& key : proj)
    {
        QJsonObject obj;

        //Enregistrer le nom du projecteur.
        obj["Name"] = key->get_name();

        //Enregistrer les coordonnées du projecteur.
        QJsonArray pos;
        pos.append(key->get_pos().x());
        pos.append(key->get_pos().y());
        pos.append(key->get_pos().z());
        obj["Position"] = pos;

        //Enregistrer l'address du projecteur.
        obj["Address"] = key->get_address();

        //Enregistrer le mode du projecteur.
        obj["Mode"] = key->get_mode();

        //Enregistrer la couleur du projecteur.
        obj["Color"] = key->get_color().name();

        //Enregistrer l'angle du faisceau du projecteur.
        obj["Angle"] = key->get_angle();

        //Enregistrer la taille du projecteur.
        QJsonArray sizeArray;
        sizeArray.append(key->get_size().height); // largeur
        sizeArray.append(key->get_size().width); // longeur
        sizeArray.append(key->get_size().dimension); //hauteur
        obj["Size"] = sizeArray;

        //distance entre l'axe de rotation et le projecteur
        obj["Distance_attache_rotation"] = key->get_distance_attache_rotation();


        convertQlistToArray.append(obj);
    }

    this->Projector = convertQlistToArray;
}

//geter


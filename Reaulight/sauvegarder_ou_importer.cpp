#include "sauvegarder_ou_importer.h"

Save_or_import::Save_or_import(QObject *parent)
    : QObject(parent), saveButton(nullptr), creatorNameInput(nullptr), roomNameInput(nullptr)
{
    saveButton = new QPushButton("Save");
    creatorNameInput = new QLineEdit();
    roomNameInput = new QLineEdit();
}

void Save_or_import::init(QWidget *window)
{
    this->MainWindow = window;
    // Récupère directement le chemin du dossier Documents
    this->defaultpath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void Save_or_import::saveParty()
{
    QWidget *enterLastData_window = new QWidget();
    enterLastData_window->setGeometry(MainWindow->width() / 2 - 250, MainWindow->height() / 2 - 100, 500, 200);
    enterLastData_window->setMaximumSize(500, 200);
    enterLastData_window->setMinimumSize(500, 200);
    enterLastData_window->setWindowTitle("Other details for save");
    enterLastData_window->setWindowIcon(MainWindow->windowIcon());

    // font commune au input ainsi qu'au texte
    QFont text_font;
    text_font.setPointSize(10);
    QFont input_font;
    input_font.setPointSize(9);

    //titre
    QLabel* title = new QLabel(enterLastData_window);
    title->setText("Reaulight");
    title->move(217, 8);

    //font du titre
    QFont title_font;
    title_font.setPointSize(15);
    title->setFont(title_font);

    //text associé a l'input si dessous (entrer le nom du créateur)
    QLabel* text1 = new QLabel(enterLastData_window);
    text1->setText("Creator Name :");
    text1->move(26,70);
    text1->setFont(text_font);

    //input
    creatorNameInput = new QLineEdit(enterLastData_window);
    creatorNameInput->setGeometry(26,90, 248, 30);
    creatorNameInput->setFont(input_font);

    //text associé a l'input si dessous (entrer le nom de la salle)
    QLabel* text2 = new QLabel(enterLastData_window);
    text2->setText("Room Name :");
    text2->move(26,130);
    text2->setFont(text_font);

    roomNameInput = new QLineEdit(enterLastData_window);
    roomNameInput->setGeometry(26,150, 248, 30);
    roomNameInput->setFont(input_font);

    //bouton de sauvegarde
    saveButton = new QPushButton(enterLastData_window);
    saveButton->setText("Save");
    saveButton->setGeometry(400, 165, 90, 25);
    saveButton->setStyleSheet(
        "QPushButton {"
        "background: rgba(17, 0, 255, 1);"
        "color: rgba(255, 255, 255, 1);"
        "border-radius: 10px;"
        "}"
        );
    QFont saveButton_font;
    saveButton_font.setPointSize(15);
    saveButton->setFont(saveButton_font);
    saveButton->setCursor(Qt::PointingHandCursor);

    //afficher le widget "enterLastData_window"
    enterLastData_window->show();

    connect(saveButton, &QPushButton::clicked, [this, enterLastData_window](){
        bool rNi = false; // room Name input
        bool cNi = false; // creator Name input

        if(roomNameInput->text().isEmpty())
        {
            QMessageBox::warning(&setOtherFileInfo, "Error", "Room name cannot be empty.");
        }
        else
        {
            rNi = true;
        }
        if(creatorNameInput->text().isEmpty())
        {
            QMessageBox::warning(&setOtherFileInfo, "Error", "The creator name is empty so your name is 'Anonymous'");
            creatorNameInput->setText("Anonymous"); // mettre le nom du créateur en anonyme
            cNi = true;
        }
        else
        {
            cNi = true;
        }
        if(cNi && rNi)
        {
            this->roomName = roomNameInput->text();
            this->creator = creatorNameInput->text();

            emit isSavingAccept(true);

            QJsonObject jsonObject;
            saveDateTime = QDate::currentDate().toString() + " at " + QTime::currentTime().toString(); // date de l'enregistrement

            QString filename = roomName;
            if(filename.contains(" "))
            {
                filename.replace(" ", "_");
            }
            fileSave = this->pathChoose + "/"+ "Reaulight_" + filename + ".json";

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

            // detruire "enterLastData_window" plutard
            enterLastData_window->deleteLater();
        }
    });
}

void Save_or_import::importParty(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray sBuf = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(sBuf);
    if (doc.isNull()) {
        qWarning() << "The content of the file is not a valid JSON.";
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
        messageBox.setWindowTitle("Error");
        messageBox.setText("You didn't record your scene.");
        messageBox.setIcon(QMessageBox::Warning);

        QPushButton* saveButton = messageBox.addButton("Save", QMessageBox::AcceptRole);
        QPushButton* cancelButton = messageBox.addButton("Cancel", QMessageBox::RejectRole);

        messageBox.exec();

        if (messageBox.clickedButton() == saveButton)
        {
            this->saveParty();
        }
    }
    //reste du code ici
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


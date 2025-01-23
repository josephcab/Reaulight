#include "sauvegarder_ou_import.h"

sauvegarder_ou_importer::sauvegarder_ou_importer() {}

void sauvegarder_ou_importer::init()
{
    // Récupérer le chemin du dossier Documents de l'utilisateur.
    this->defaultpath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    this->defaultpath.append("/Documents");
}
void sauvegarder_ou_importer::saveParty()
{

}
void sauvegarder_ou_importer::importParty()
{
    return;
}
void sauvegarder_ou_importer::dialog(dialogType type)
{

    if(type == import)
    {
        this->import_file = QFileDialog::getOpenFileName(nullptr, "Open File",this->pathChoose.isEmpty() ? this->defaultpath : this->pathChoose,"JSON Files (*.json);");
        this->importParty(); // Lancer le code pour lire et importer toutes les données du fichier JSON
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

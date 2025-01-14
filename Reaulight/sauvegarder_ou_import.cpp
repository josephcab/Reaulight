#include "sauvegarder_ou_import.h"

sauvegarder_ou_importer::sauvegarder_ou_importer() {}

void sauvegarder_ou_importer::init()
{
    //recup le path Documents de l'utiliseurs.
    this->defaultpath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    this->defaultpath.append("/Documents");
}
void sauvegarder_ou_importer::saveParty()
{

}
void sauvegarder_ou_importer::importParty()
{

}
void sauvegarder_ou_importer::dialog(dialogType type)
{
    QMessageBox msgbox;
    if(type == dialogType::import)
    {
        return;
    }
    if(type == dialogType::save)
    {

    }
}

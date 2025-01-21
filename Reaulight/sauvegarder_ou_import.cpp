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
    return;
}
void sauvegarder_ou_importer::dialog(dialogType type)
{
    QMessageBox msgbox;
    msgbox.setBaseSize(1000, 500);

    if(type == dialogType::import)
    {
        msgbox.setWindowTitle("IMPORT d'une scène.");
    }
    if(type == dialogType::save)
    {
        msgbox.setWindowTitle("SAUVEGARDE d'une scène.");
    }

    if(msgbox.exec())
    {
        return;
    }
}

#include "DTOUsuari.h"

DTOUsuari::DTOUsuari(const std::string& sobrenom, const std::string& nom, const std::string& correu,
    const std::string& contrasenya, const std::string& dataNaixement, const std::string& modalitat)
    : sobrenom(sobrenom), nom(nom), correuElectronic(correu), contrasenya(contrasenya),
    dataNaixement(dataNaixement), modalitatSubscripcio(modalitat) {}

std::string DTOUsuari::obteSobrenom() const { return sobrenom; }
std::string DTOUsuari::obteNom() const { return nom; }
std::string DTOUsuari::obteCorreu() const { return correuElectronic; }
std::string DTOUsuari::obteContrasenya() const { return contrasenya; }
std::string DTOUsuari::obteDataNaixement() const { return dataNaixement; }
std::string DTOUsuari::obteModalitat() const { return modalitatSubscripcio; }

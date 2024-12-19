#ifndef DTO_USUARI_H
#define DTO_USUARI_H

#include <string>

class DTOUsuari {
public:
    DTOUsuari(const std::string& sobrenom, const std::string& nom, const std::string& correu,
        const std::string& contrasenya, const std::string& dataNaixement, const std::string& modalitat);

    std::string obteSobrenom() const;
    std::string obteNom() const;
    std::string obteCorreu() const;
    std::string obteContrasenya() const;
    std::string obteDataNaixement() const;
    std::string obteModalitat() const;

private:
    std::string sobrenom;
    std::string nom;
    std::string correuElectronic;
    std::string contrasenya;
    std::string dataNaixement;
    std::string modalitatSubscripcio;
};

#endif

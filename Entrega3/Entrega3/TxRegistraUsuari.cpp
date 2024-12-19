#include "TxRegistraUsuari.h"
#include "PassarellaUsuari.h"
#include <stdexcept>

void TxRegistraUsuari::crear(const std::string& nom, const std::string& sobrenom, const std::string& contrasenya,
    const std::string& correu, const std::string& dataNaixement, const std::string& modalitatSubscripcio) {
    nomU = nom;
    sobrenomU = sobrenom;
    contrasenyaU = contrasenya;
    correuElectronicU = correu;
    dataNaixementU = dataNaixement;
    modalitatSubscripcioU = modalitatSubscripcio;
}

void TxRegistraUsuari::executar() {
    PassarellaUsuari usuari(sobrenomU, nomU, correuElectronicU, contrasenyaU, dataNaixementU, modalitatSubscripcioU);
    usuari.insereix();
}

#include "TxRegistraUsuari.h"
#include "CercadoraUsuari.h"
#include <stdexcept>

void TxRegistraUsuari::crear(const std::string& nom, const std::string& sobrenom, const std::string& contrasenya,
    const std::string& correu, const std::string& dataNaixement, const std::string& modalitatSubscripcio) {
    nomU = nom;
    sobrenomU = sobrenom;
    contrasenyaU = contrasenya;
    correuElectronicU = correu;
    dataNaixementU = dataNaixement;

    // Validar modalidad
    if (modalitatSubscripcio != "Completa" && modalitatSubscripcio != "Cinefil" && modalitatSubscripcio != "Infantil") {
        throw std::invalid_argument("Modalitat no existeix.");
    }
    modalitatSubscripcioU = modalitatSubscripcio;
}

void TxRegistraUsuari::executar() {
    // Verificar si el sobrenom o correo ya existen
    CercadoraUsuari cercador;

    try {
        cercador.cercaPerSobrenom(sobrenomU);
        throw std::runtime_error("El sobrenom ja existeix.");
    }
    catch (const std::exception&) {
        // Continuar si no existe el usuario
    }

    PassarellaUsuari usuari(sobrenomU, nomU, correuElectronicU, contrasenyaU, dataNaixementU, modalitatSubscripcioU);
    usuari.insereix();
}

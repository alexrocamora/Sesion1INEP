#include "TxIniciSessio.h"
#include "PetitFlix.h"
#include "CercadoraUsuari.h"
#include <stdexcept>

TxIniciSessio::TxIniciSessio() : sobrenomU(""), contrasenyaU("") {}

void TxIniciSessio::crear(const std::string& sobrenom, const std::string& contrasenya) {
    sobrenomU = sobrenom;
    contrasenyaU = contrasenya;
}

void TxIniciSessio::executar() {
    CercadoraUsuari cercador;
    usuari = cercador.cercaPerSobrenom(sobrenomU);

    if (usuari.obteContrasenya() != contrasenyaU) {
        throw std::runtime_error("Error: Contrasenya incorrecta.");
    }

    PetitFlix::getInstance()->iniciaSessio(usuari);
}

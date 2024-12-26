#include "TxEsborraUsuari.h"
#include "CercadoraUsuari.h"
#include "PassarellaUsuari.h"
#include <stdexcept>

void TxEsborraUsuari::crear(const std::string& sobrenom, const std::string& contrasenya) {
    sobrenomU = sobrenom;
    contrasenyaU = contrasenya;
}

void TxEsborraUsuari::executar() {
    CercadoraUsuari cercador;
    PassarellaUsuari usuari = cercador.cercaPerSobrenom(sobrenomU);

    // Validar la contraseña
    if (usuari.obteContrasenya() != contrasenyaU) {
        throw std::runtime_error("Contrasenya incorrecta");
    }

    // Borrar al usuario
    usuari.esborra();
}

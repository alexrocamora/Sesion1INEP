#include "TxEsborraUsuari.h"
#include "CercadoraUsuari.h"
#include "PassarellaUsuari.h"
#include <stdexcept>

void TxEsborraUsuari::crear(const std::string& sobrenom) {
    contraU = sobrenom;
}

void TxEsborraUsuari::executar() {
    CercadoraUsuari cercador;
    PassarellaUsuari usuari = cercador.cercaPerSobrenom(contraU);
    usuari.esborra();
}

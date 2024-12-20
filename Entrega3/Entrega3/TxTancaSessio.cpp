#include "TxTancaSessio.h"
#include "PetitFlix.h"

void TxTancaSessio::crear() {
    // No necesita inicializar parámetros específicos
}

void TxTancaSessio::executar() {
    PetitFlix::getInstance()->tancaSessio();
}

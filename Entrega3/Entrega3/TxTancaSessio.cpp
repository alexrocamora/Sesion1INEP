#include "TxTancaSessio.h"
#include "PetitFlix.h"

void TxTancaSessio::crear() {
    // No necesita inicializar par�metros espec�ficos
}

void TxTancaSessio::executar() {
    PetitFlix::getInstance()->tancaSessio();
}

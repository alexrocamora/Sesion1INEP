#ifndef TX_INICI_SESSIO_H
#define TX_INICI_SESSIO_H

#include <string>
#include "PassarellaUsuari.h"

class TxIniciSessio {
public:
    TxIniciSessio();
    void crear(const std::string& sobrenom, const std::string& contrasenya);
    void executar();

private:
    std::string sobrenomU;
    std::string contrasenyaU;
    PassarellaUsuari usuari;
};

#endif

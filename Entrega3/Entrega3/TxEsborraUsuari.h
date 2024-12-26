#ifndef TX_ESBORRA_USUARI_H
#define TX_ESBORRA_USUARI_H

#include <string>

class TxEsborraUsuari {
public:
    void crear(const std::string& sobrenom, const std::string& contrasenya);
    void executar();

private:
    std::string sobrenomU;
    std::string contrasenyaU;
};

#endif

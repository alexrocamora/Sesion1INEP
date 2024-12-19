#ifndef TX_ESBORRA_USUARI_H
#define TX_ESBORRA_USUARI_H

#include <string>

class TxEsborraUsuari {
public:
    void crear(const std::string& sobrenom);
    void executar();

private:
    std::string contraU;
};

#endif

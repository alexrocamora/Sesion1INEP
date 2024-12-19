#ifndef TX_REGISTRA_USUARI_H
#define TX_REGISTRA_USUARI_H

#include <string>

class TxRegistraUsuari {
public:
    void crear(const std::string& nom, const std::string& sobrenom, const std::string& contrasenya,
        const std::string& correu, const std::string& dataNaixement, const std::string& modalitatSubscripcio);
    void executar();

private:
    std::string nomU, sobrenomU, contrasenyaU, correuElectronicU, dataNaixementU, modalitatSubscripcioU;
};

#endif

#ifndef PETITFLIX_H
#define PETITFLIX_H

#include "PassarellaUsuari.h"
#include <memory>

class PetitFlix {
public:
    static PetitFlix* getInstance();
    void iniciaSessio(const PassarellaUsuari& usuari);
    void tancaSessio();
    PassarellaUsuari obteUsuari() const;

private:
    PetitFlix() = default;
    static PetitFlix* instancia;
    std::unique_ptr<PassarellaUsuari> usuariActual;
};

#endif

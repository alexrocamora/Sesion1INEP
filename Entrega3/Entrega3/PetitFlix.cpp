#include "PetitFlix.h"
#include <stdexcept>

PetitFlix* PetitFlix::instancia = nullptr;

PetitFlix* PetitFlix::getInstance() {
    if (!instancia) {
        instancia = new PetitFlix();
    }
    return instancia;
}

void PetitFlix::iniciaSessio(const PassarellaUsuari& usuari) {
    usuariActual = std::make_unique<PassarellaUsuari>(usuari);
}

void PetitFlix::tancaSessio() {
    usuariActual.reset();
}

PassarellaUsuari PetitFlix::obteUsuari() const {
    if (!usuariActual) {
        throw std::runtime_error("Error: No hi ha cap usuari loggejat.");
    }
    return *usuariActual;
}

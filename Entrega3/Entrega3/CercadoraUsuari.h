#ifndef CERCADORA_USUARI_H
#define CERCADORA_USUARI_H

#include "PassarellaUsuari.h"
#include <vector>

class CercadoraUsuari {
public:
    PassarellaUsuari cercaPerSobrenom(const std::string& sobrenom);
    std::vector<PassarellaUsuari> cercaTots();
};

#endif



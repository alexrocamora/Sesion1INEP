#ifndef CERCADORA_CONTINGUT_H
#define CERCADORA_CONTINGUT_H

#include <string>
#include <vector>
#include "PassarellaContingut.h"

class CercadoraContingut {
public:
    std::vector<PassarellaContingut> cercaProperesEstrenes(const std::string& subscripcio);
};

#endif

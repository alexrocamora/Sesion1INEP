#ifndef CERCADORA_CONTINGUT_H
#define CERCADORA_CONTINGUT_H

#include <string>
#include <vector>
#include "PassarellaProperesEstrenes.h"

class CercadoraContingut {
public:
    std::vector<PassarellaProperesEstrenes> cercaProperesEstrenes(const std::string& subscripcio);
};

#endif

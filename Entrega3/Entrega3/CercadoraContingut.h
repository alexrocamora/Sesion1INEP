#ifndef CERCADORA_CONTINGUT_H
#define CERCADORA_CONTINGUT_H

#include <string>
#include <vector>
#include "PassarellaProperesEstrenes.h"
#include "PassarellaUltimesNovetats.h"

class CercadoraContingut {
public:
    std::vector<PassarellaProperesEstrenes> cercaProperesEstrenes(const std::string& subscripcio);
    std::vector<PassarellaProperesEstrenes> cercaUltimesNovetatsPel(const std::string& subscripcio);
    std::vector<PassarellaUltimesNovetats> cercaUltimesNovetatsSer(const std::string& subscripcio);
};

#endif

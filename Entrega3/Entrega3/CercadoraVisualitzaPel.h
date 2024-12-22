#ifndef CERCADORA_VISUALITZA_PEL_H
#define CERCADORA_VISUALITZA_PEL_H

#include <string>
#include <vector>
#include "PassarellaVisualitzaPel.h"

class CercadoraVisualitzaPel {
public:
    PassarellaVisualitzaPel cercaPerTitol(const std::string& titol);
    int cercaNumVisualitzacions(const std::string& sobrenomUsuari);
    std::vector<PassarellaVisualitzaPel> cercaTopVisualitzacions();
    std::vector<PassarellaVisualitzaPel> cercaVisualitzacionsPerUsuari(const std::string& sobrenomUsuari);

};

#endif

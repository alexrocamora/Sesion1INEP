#ifndef CERCADORA_VISUALITZA_SERIE_H
#define CERCADORA_VISUALITZA_SERIE_H

#include <string>
#include <vector>
#include "PassarellaVisualitzaSerie.h"

class CercadoraVisualitzaSerie {
public:
    PassarellaVisualitzaSerie cercaPerTitol(const std::string& titolSerie, int temporada, int capitol);
    int cercaNumVisualitzacions(const std::string& sobrenomUsuari);
    std::vector<PassarellaVisualitzaSerie> cercaTopVisualitzacions();
};

#endif

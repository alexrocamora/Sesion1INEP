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
    std::vector<PassarellaVisualitzaSerie> cercaVisualitzacionsPerUsuari(const std::string& sobrenomUsuari);
    std::vector<int> obteTemporades(const std::string& titolSerie);  
    std::vector<PassarellaVisualitzaSerie> obteCapitols(const std::string& titolSerie, int numTemporada);
    std::vector<std::string> cercaSeriesRelacionades(const std::string& titolSerie);
    void registraVisualitzacio(const std::string& sobrenom, const std::string& titolSerie,
        int temporada, int capitol);
};

#endif

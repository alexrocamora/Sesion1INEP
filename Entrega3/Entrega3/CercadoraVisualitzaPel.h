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
    PassarellaVisualitzaPel cercaPerTitolComplet(const std::string& titol); 
    void registraVisualitzacio(const std::string& sobrenomUsuari, const std::string& titol, const std::string& data);
    std::vector<std::string> cercaPeliculesRelacionades(const std::string& titol);

};

#endif

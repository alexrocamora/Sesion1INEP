#include "PassarellaContingut.h"

PassarellaContingut::PassarellaContingut(const std::string& titol, 
    const std::string& dataEstrena, const std::string& qualificacioEdat, 
    int duracio, const std::string& tipus)
    : titolPelicula(titol), dataEstrena(dataEstrena), qualificacioEdat(qualificacioEdat),
    duracio(duracio), tipus(tipus) {}

std::string PassarellaContingut::obteTitol() const {
    return titolPelicula;
}

std::string PassarellaContingut::obteDataEstrena() const {
    return dataEstrena;
}

std::string PassarellaContingut::obteQualificacioEdat() const {
    return qualificacioEdat;
}

int PassarellaContingut::obteDuracio() const {
    return duracio;
}

std::string PassarellaContingut::obteTipus() const {
    return tipus;
}
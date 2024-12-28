#include "PassarellaProperesEstrenes.h"

PassarellaProperesEstrenes::PassarellaProperesEstrenes(const std::string& titol, 
    const std::string& dataEstrena, const std::string& qualificacioEdat, 
    int duracio, const std::string& tipus)
    : titol(titol), dataEstrena(dataEstrena), qualificacioEdat(qualificacioEdat),
    duracio(duracio), tipus(tipus) {}

std::string PassarellaProperesEstrenes::obteTitol() const {
    return titol;
}

std::string PassarellaProperesEstrenes::obteDataEstrena() const {
    return dataEstrena;
}

std::string PassarellaProperesEstrenes::obteQualificacioEdat() const {
    return qualificacioEdat;
}

int PassarellaProperesEstrenes::obteDuracio() const {
    return duracio;
}

std::string PassarellaProperesEstrenes::obteTipus() const {
    return tipus;
}
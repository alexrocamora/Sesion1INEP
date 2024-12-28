#include "PassarellaUltimesNovetats.h"

PassarellaUltimesNovetats::PassarellaUltimesNovetats(const std::string& titol, 
    const std::string& dataEstrena, const std::string& qualificacioEdat, 
    const std::string& temporada, const std::string& capitol, const std::string& tipus)
    : titol(titol), dataEstrena(dataEstrena), qualificacioEdat(qualificacioEdat), 
    temporada(temporada), capitol(capitol), tipus(tipus) {}

std::string PassarellaUltimesNovetats::obteTitol() const {
    return titol;
}

std::string PassarellaUltimesNovetats::obteDataEstrena() const {
    return dataEstrena;
}

std::string PassarellaUltimesNovetats::obteQualificacioEdat() const {
    return qualificacioEdat;
}

std::string PassarellaUltimesNovetats::obteTemporada() const {
    return temporada;
}

std::string PassarellaUltimesNovetats::obteCapitol() const {
    return capitol;
}

std::string PassarellaUltimesNovetats::obteTipus() const {
    return tipus;
}
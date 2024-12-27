#include "PassarellaVisualitzaPel.h"

PassarellaVisualitzaPel::PassarellaVisualitzaPel(const std::string& sobrenom, const std::string& titol,
    const std::string& data, int numVisualitzacions,
    const std::string& descripcio, int qualificacioEdat,
    int duracio, const std::string& dataEstrena)
    : sobrenomUsuari(sobrenom), titolPelicula(titol), data(data),
    numVisualitzacions(numVisualitzacions), descripcio(descripcio),
    qualificacioEdat(qualificacioEdat), duracio(duracio),
    dataEstrena(dataEstrena) {}

std::string PassarellaVisualitzaPel::obteSobrenom() const {
    return sobrenomUsuari;
}

std::string PassarellaVisualitzaPel::obteTitol() const {
    return titolPelicula;
}

std::string PassarellaVisualitzaPel::obteData() const {
    return data;
}

int PassarellaVisualitzaPel::obteNumVisualitzacions() const {
    return numVisualitzacions;
}

std::string PassarellaVisualitzaPel::obteDescripcio() const {
    return descripcio;
}

int PassarellaVisualitzaPel::obteQualificacioEdat() const {
    return qualificacioEdat;
}

int PassarellaVisualitzaPel::obteDuracio() const {
    return duracio;
}

std::string PassarellaVisualitzaPel::obteDataEstrena() const {
    return dataEstrena;
}

#include "PassarellaVisualitzaPel.h"

PassarellaVisualitzaPel::PassarellaVisualitzaPel(const std::string& sobrenom, const std::string& titol,
    const std::string& data, int numVisualitzacions)
    : sobrenomUsuari(sobrenom), titolPelicula(titol), data(data), numVisualitzacions(numVisualitzacions) {}

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

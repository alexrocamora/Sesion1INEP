#include "PassarellaVisualitzaSerie.h"

PassarellaVisualitzaSerie::PassarellaVisualitzaSerie(const std::string& sobrenom, const std::string& titol,
    int temporada, int capitol, const std::string& data, int numVisualitzacions)
    : sobrenomUsuari(sobrenom), titolSerie(titol), numTemporada(temporada),
    numCapitol(capitol), data(data), numVisualitzacions(numVisualitzacions) {}

std::string PassarellaVisualitzaSerie::obteSobrenom() const {
    return sobrenomUsuari;
}

std::string PassarellaVisualitzaSerie::obteTitol() const {
    return titolSerie;
}

int PassarellaVisualitzaSerie::obteTemporada() const {
    return numTemporada;
}

int PassarellaVisualitzaSerie::obteCapitol() const {
    return numCapitol;
}

std::string PassarellaVisualitzaSerie::obteData() const {
    return data;
}

int PassarellaVisualitzaSerie::obteNumVisualitzacions() const {
    return numVisualitzacions;
}

#include "TxInfoVisualitzacions.h"
#include "CercadoraVisualitzaPel.h"
#include "CercadoraVisualitzaSerie.h"

void TxInfoVisualitzacions::crear(const std::string& sobrenomUsuari) {
    sobrenomU = sobrenomUsuari;
    peliculesVisualitzades = 0;
    seriesVisualitzades = 0;
}

void TxInfoVisualitzacions::executar() {
    CercadoraVisualitzaPel cercadoraPel;
    CercadoraVisualitzaSerie cercadoraSerie;

    peliculesVisualitzades = cercadoraPel.cercaNumVisualitzacions(sobrenomU);
    seriesVisualitzades = cercadoraSerie.cercaNumVisualitzacions(sobrenomU);
}

int TxInfoVisualitzacions::obteResultatPelicules() const {
    return peliculesVisualitzades;
}

int TxInfoVisualitzacions::obteResultatSeries() const {
    return seriesVisualitzades;
}

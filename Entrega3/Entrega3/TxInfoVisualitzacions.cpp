#include "TxInfoVisualitzacions.h"
#include "CercadoraVisualitzaPel.h"
#include "CercadoraVisualitzaSerie.h"
#include <iostream>

void TxInfoVisualitzacions::crear(const std::string& sobrenomUsuari) {
    sobrenomU = sobrenomUsuari;
    peliculesVisualitzades = 0;
    seriesVisualitzades = 0;
    detallPelicules.clear();
    detallSeries.clear();
}

void TxInfoVisualitzacions::executar() {
    CercadoraVisualitzaPel cercadoraPel;
    CercadoraVisualitzaSerie cercadoraSerie;

    // Obtener el total de visualizaciones
    peliculesVisualitzades = cercadoraPel.cercaNumVisualitzacions(sobrenomU);
    seriesVisualitzades = cercadoraSerie.cercaNumVisualitzacions(sobrenomU);

    // Obtener detalles de las visualizaciones
    detallPelicules = cercadoraPel.cercaVisualitzacionsPerUsuari(sobrenomU);
    detallSeries = cercadoraSerie.cercaVisualitzacionsPerUsuari(sobrenomU);
}

int TxInfoVisualitzacions::obteResultatPelicules() const {
    return peliculesVisualitzades;
}

int TxInfoVisualitzacions::obteResultatSeries() const {
    return seriesVisualitzades;
}

void TxInfoVisualitzacions::mostrarDetallsPelicules() const {
    if (detallPelicules.empty()) {
        std::cout << "No s'han trobat visualitzacions de pel·lícules per a aquest usuari.\n";
        return;
    }

    std::cout << "=== Detalls de Pel·lícules ===\n";
    PassarellaVisualitzaPel mesVista = detallPelicules[0];

    for (const auto& pel : detallPelicules) {
        std::cout << "- Pel·lícula: " << pel.obteTitol()
            << " - Visualitzacions: " << pel.obteNumVisualitzacions() << "\n";
        if (pel.obteNumVisualitzacions() > mesVista.obteNumVisualitzacions()) {
            mesVista = pel;
        }
    }

    std::cout << "Pel·lícula més vista: " << mesVista.obteTitol()
        << " amb " << mesVista.obteNumVisualitzacions() << " visualitzacions.\n";
}

void TxInfoVisualitzacions::mostrarDetallsSeries() const {
    if (detallSeries.empty()) {
        std::cout << "No s'han trobat visualitzacions de sèries per a aquest usuari.\n";
        return;
    }

    std::cout << "=== Detalls de Sèries ===\n";
    PassarellaVisualitzaSerie mesVista = detallSeries[0];

    for (const auto& serie : detallSeries) {
        std::cout << "- Sèrie: " << serie.obteTitol()
            << " - Temporada: " << serie.obteTemporada()
            << " - Capítol: " << serie.obteCapitol()
            << " - Visualitzacions: " << serie.obteNumVisualitzacions() << "\n";
        if (serie.obteNumVisualitzacions() > mesVista.obteNumVisualitzacions()) {
            mesVista = serie;
        }
    }

    std::cout << "Sèrie més vista: " << mesVista.obteTitol()
        << " (Temporada " << mesVista.obteTemporada()
        << ", Capítol " << mesVista.obteCapitol() << ") amb "
        << mesVista.obteNumVisualitzacions() << " visualitzacions.\n";
}

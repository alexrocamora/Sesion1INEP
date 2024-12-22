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
        std::cout << "No s'han trobat visualitzacions de pel�l�cules per a aquest usuari.\n";
        return;
    }

    std::cout << "=== Detalls de Pel�l�cules ===\n";
    PassarellaVisualitzaPel mesVista = detallPelicules[0];

    for (const auto& pel : detallPelicules) {
        std::cout << "- Pel�l�cula: " << pel.obteTitol()
            << " - Visualitzacions: " << pel.obteNumVisualitzacions() << "\n";
        if (pel.obteNumVisualitzacions() > mesVista.obteNumVisualitzacions()) {
            mesVista = pel;
        }
    }

    std::cout << "Pel�l�cula m�s vista: " << mesVista.obteTitol()
        << " amb " << mesVista.obteNumVisualitzacions() << " visualitzacions.\n";
}

void TxInfoVisualitzacions::mostrarDetallsSeries() const {
    if (detallSeries.empty()) {
        std::cout << "No s'han trobat visualitzacions de s�ries per a aquest usuari.\n";
        return;
    }

    std::cout << "=== Detalls de S�ries ===\n";
    PassarellaVisualitzaSerie mesVista = detallSeries[0];

    for (const auto& serie : detallSeries) {
        std::cout << "- S�rie: " << serie.obteTitol()
            << " - Temporada: " << serie.obteTemporada()
            << " - Cap�tol: " << serie.obteCapitol()
            << " - Visualitzacions: " << serie.obteNumVisualitzacions() << "\n";
        if (serie.obteNumVisualitzacions() > mesVista.obteNumVisualitzacions()) {
            mesVista = serie;
        }
    }

    std::cout << "S�rie m�s vista: " << mesVista.obteTitol()
        << " (Temporada " << mesVista.obteTemporada()
        << ", Cap�tol " << mesVista.obteCapitol() << ") amb "
        << mesVista.obteNumVisualitzacions() << " visualitzacions.\n";
}

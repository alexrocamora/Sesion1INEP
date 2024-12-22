#ifndef TX_INFO_VISUALITZACIONS_H
#define TX_INFO_VISUALITZACIONS_H

#include <string>
#include <vector>
#include "PassarellaVisualitzaPel.h"
#include "PassarellaVisualitzaSerie.h"

class TxInfoVisualitzacions {
public:
    void crear(const std::string& sobrenomUsuari);
    void executar();

    int obteResultatPelicules() const;
    int obteResultatSeries() const;

    void mostrarDetallsPelicules() const;
    void mostrarDetallsSeries() const;

private:
    std::string sobrenomU;
    int peliculesVisualitzades;
    int seriesVisualitzades;

    std::vector<PassarellaVisualitzaPel> detallPelicules;
    std::vector<PassarellaVisualitzaSerie> detallSeries;
};

#endif

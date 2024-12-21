#ifndef TX_INFO_VISUALITZACIONS_H
#define TX_INFO_VISUALITZACIONS_H

#include <string>
#include "DTOUsuari.h"

class TxInfoVisualitzacions {
public:
    void crear(const std::string& sobrenomUsuari);
    void executar();
    int obteResultatPelicules() const;
    int obteResultatSeries() const;

private:
    std::string sobrenomU;
    int peliculesVisualitzades;
    int seriesVisualitzades;
};

#endif

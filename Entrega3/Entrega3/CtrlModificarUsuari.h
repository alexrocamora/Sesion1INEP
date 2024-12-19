#ifndef CTRL_MODIFICAR_USUARI_H
#define CTRL_MODIFICAR_USUARI_H

#include "DTOUsuari.h"
#include "PassarellaUsuari.h"

class CtrlModificarUsuari {
public:
    DTOUsuari consultaUsuari(const std::string& sobrenom);
    void modificaUsuari(const DTOUsuari& dtoUsuari);
};

#endif

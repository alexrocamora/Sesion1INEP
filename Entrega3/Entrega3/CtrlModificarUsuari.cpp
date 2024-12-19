#include "CtrlModificarUsuari.h"
#include "CercadoraUsuari.h"

DTOUsuari CtrlModificarUsuari::consultaUsuari(const std::string& sobrenom) {
    CercadoraUsuari cercador;
    PassarellaUsuari usuari = cercador.cercaPerSobrenom(sobrenom);

    return DTOUsuari(usuari.obteSobrenom(), usuari.obteNom(), usuari.obteCorreuElectronic(),
        usuari.obteContrasenya(), usuari.obteDataNaixement(), usuari.obteModalitatSubscripcio());
}

void CtrlModificarUsuari::modificaUsuari(const DTOUsuari& dtoUsuari) {
    CercadoraUsuari cercador;
    PassarellaUsuari usuari = cercador.cercaPerSobrenom(dtoUsuari.obteSobrenom());

    usuari.posaNom(dtoUsuari.obteNom());
    usuari.posaContrasenya(dtoUsuari.obteContrasenya());
    usuari.posaCorreuElectronic(dtoUsuari.obteCorreu());
    usuari.posaDataNaixement(dtoUsuari.obteDataNaixement());
    usuari.posaModalitatSubscripcio(dtoUsuari.obteModalitat());

    usuari.modifica();
}

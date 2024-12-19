#include "TxConsultaUsuari.h"
#include "CercadoraUsuari.h"

TxConsultaUsuari::TxConsultaUsuari()
    : resultat("", "", "", "", "", ""), usuari("", "", "", "", "", "") {}

void TxConsultaUsuari::crear() {
    // Implementación según los requisitos del flujo
}

void TxConsultaUsuari::executar() {
    CercadoraUsuari cercador;
    usuari = cercador.cercaPerSobrenom(resultat.obteSobrenom());

    resultat = DTOUsuari(usuari.obteSobrenom(), usuari.obteNom(), usuari.obteCorreuElectronic(),
        usuari.obteContrasenya(), usuari.obteDataNaixement(), usuari.obteModalitatSubscripcio());
}

DTOUsuari TxConsultaUsuari::obteResultat() const { return resultat; }

PassarellaUsuari TxConsultaUsuari::obteUsuari() const { return usuari; }
